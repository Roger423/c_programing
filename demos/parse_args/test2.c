
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/* ========================================================================= */
/* 1. 原始定义 (保持不变)                                                    */
/* ========================================================================= */
// ... (ipc_common_msg_t, enums, etc. definitions are assumed to be here) ...
#define IPC_COMMON_MSG_LEN_IN_DW      (8)
#define PSW_IPC_CALLBACK
typedef uint32_t u32;
typedef uint8_t u8;
typedef union { struct { u32 DW[IPC_COMMON_MSG_LEN_IN_DW]; }; struct { union { struct { u32 opcode : 8; u32 sub_opcode : 8; u32 rsvd : 8; u32 flags : 8; }; struct { u32 : 8; u32 : 8; u32 err : 8; u32 status : 8; }; } hdr; u32 context[6]; u32 user_tag : 8; u32 dest : 4; u32 source : 4; u32 msg_type : 2; u32 rsvd_footer : 6; u32 check_sum : 8; }; } ipc_common_msg_t;
typedef enum { IPC_OP_SYS_DBG = 3, } ipc_opcode_e;
typedef enum { IPC_SUB_OP_VIRTIO = 0, IPC_SUB_OP_DEBUG, IPC_SUB_OP_FLOW_LOG, IPC_SUB_OP_DST_MAC, IPC_SUB_OP_HASH, IPC_SUB_OP_MAC_PORT_VID, } ipc_sub_opcode_sys_dbg_e;
typedef enum { CPUID_CORE0 = 0, CPUID_CORE1, CPUID_CORE2, CPUID_CORE3, CPUID_MAX, } ipc_cpuid_e;
typedef enum { MSG_REQ = 0, MSG_REP, MAX_MSG_TYPE, } ipc_msg_type_e;
void ipc_msg_req_hdr_init(ipc_common_msg_t *msg, int op, int sub_op, int flags);
void ipc_msg_common_init(ipc_common_msg_t *msg, int source, int dest, int type, int tag);
int ipc_send_msg(int core_id, ipc_common_msg_t *msg);
void infra_cli_printf(const char *fmt, ...);
void mac_str_to_bin(const char *mac_str, u8 *bin);
void str2int(const char *str, u32 *val);


/* ========================================================================= */
/* 2. 新的回调设计                                                           */
/* ========================================================================= */

// 步骤 1: 定义回调函数指针类型
typedef bool (*sysdbg_cmd_handler_t)(ipc_common_msg_t *msg, int argc, const char *argv[]);

// 步骤 2: 定义命令ID枚举
typedef enum {
    CMD_UNKNOWN = 0,
    CMD_VIRTIO,
    CMD_DEBUG,
    CMD_FLOW_LOG,
    CMD_DSTMAC,
    CMD_DSTMAC_PORT_VID,
    CMD_HASH,
    CMD_MAX // 哨兵值，必须是最后一个
} sysdbg_cmd_id_e;

// 前向声明所有处理器函数
static bool sysdbg_virtio(ipc_common_msg_t *msg, int argc, const char *argv[]);
static bool sysdbg_debug(ipc_common_msg_t *msg, int argc, const char *argv[]);
static bool sysdbg_flow_log(ipc_common_msg_t *msg, int argc, const char *argv[]);
static bool sysdbg_dstmac(ipc_common_msg_t *msg, int argc, const char *argv[]);
static bool sysdbg_dstmac_srcport_vid(ipc_common_msg_t *msg, int argc, const char *argv[]);
static bool sysdbg_hash(ipc_common_msg_t *msg, int argc, const char *argv[]);


// 步骤 3: 创建回调函数数组
// 使用 const 确保数组在运行时不被修改
static const sysdbg_cmd_handler_t sysdbg_callbacks[CMD_MAX] = {
    [CMD_UNKNOWN]         = NULL, // 索引0不对应任何有效命令
    [CMD_VIRTIO]          = sysdbg_virtio,
    [CMD_DEBUG]           = sysdbg_debug,
    [CMD_FLOW_LOG]        = sysdbg_flow_log,
    [CMD_DSTMAC]          = sysdbg_dstmac,
    [CMD_DSTMAC_PORT_VID] = sysdbg_dstmac_srcport_vid,
    [CMD_HASH]            = sysdbg_hash,
};

// 步骤 4: 更新 get_sub_cmd_type 函数，使其返回 enum
static sysdbg_cmd_id_e get_sysdbg_cmd_id(int argc, const char *argv[]) {
    if (argc < 2) return CMD_UNKNOWN;
    
    const char *sub_cmd = argv[1];

    if (strcmp(sub_cmd, "virtio") == 0) return CMD_VIRTIO;
    if (strcmp(sub_cmd, "debug") == 0) return CMD_DEBUG;
    if (strcmp(sub_cmd, "flow-log") == 0) return CMD_FLOW_LOG;
    
    if (strncmp(sub_cmd, "dstmac=", strlen("dstmac=")) == 0) {
        if (argc == 2) return CMD_DSTMAC;
        if (argc == 4 && 
            strncmp(argv[2], "srcport=", strlen("srcport=")) == 0 && 
            strncmp(argv[3], "vid=", strlen("vid=")) == 0) {
            return CMD_DSTMAC_PORT_VID;
        }
    }
    
    if (strncmp(sub_cmd, "hash=", strlen("hash=")) == 0 && argc == 2) return CMD_HASH;
    
    return CMD_UNKNOWN;
}


/* ========================================================================= */
/* 3. 主函数使用回调数组进行分发                                             */
/* ========================================================================= */

static int infra_cli_cmd_sys_dbg(int argc, const char *argv[]) {
    ipc_common_msg_t msg;
    bool success = false;

    memset(&msg, 0, sizeof(ipc_common_msg_t));

    if (argc < 2) {
        infra_cli_printf("sysdbg: input params error...\r\n");
        return -1;
    }

    // 获取命令ID (即数组索引)
    sysdbg_cmd_id_e cmd_id = get_sysdbg_cmd_id(argc, argv);

    // 索引有效性检查，并调用对应的回调函数
    if (cmd_id > CMD_UNKNOWN && cmd_id < CMD_MAX && sysdbg_callbacks[cmd_id] != NULL) {
        // 核心分发逻辑！
        success = sysdbg_callbacks[cmd_id](&msg, argc, argv);
    } else {
        infra_cli_printf("sysdbg: invalid parameters or command not supported!\r\n");
        success = false;
    }

    if (!success) {
        infra_cli_printf("sysdbg: command execution failed for [%s]\r\n", argv[1]);
    }

    return success ? 0 : -1;
}


/* ========================================================================= */
/* 4. 所有处理器函数的实现 (保持不变)                                        */
/* ========================================================================= */
// (此处省略所有 sysdbg_xxx 函数的具体实现代码，它们与上一版相同)
static bool sysdbg_virtio(ipc_common_msg_t *msg, int argc, const char *argv[]) { /* ... implementation ... */ return true; }
static bool sysdbg_debug(ipc_common_msg_t *msg, int argc, const char *argv[]) { /* ... implementation ... */ return true; }
static bool sysdbg_flow_log(ipc_common_msg_t *msg, int argc, const char *argv[]) { /* ... implementation ... */ return true; }
static bool sysdbg_dstmac(ipc_common_msg_t *msg, int argc, const char *argv[]) { /* ... implementation ... */ return true; }
static bool sysdbg_dstmac_srcport_vid(ipc_common_msg_t *msg, int argc, const char *argv[]) { /* ... implementation ... */ return true; }
static bool sysdbg_hash(ipc_common_msg_t *msg, int argc, const char *argv[]) { /* ... implementation ... */ return true; }

