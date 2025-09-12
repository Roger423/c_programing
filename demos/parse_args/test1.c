#include <stdint.h>
#include <stdbool.h>
#include <string.h> // for memset, strncmp, strlen
#include <stdlib.h> // for strtoul

/* ========================================================================= */
/* 1. 原始代码中的定义 (为了代码完整性，在此包含)                          */
/* ========================================================================= */

#define IPC_COMMON_MSG_LEN_IN_DW      (8)
#define PSW_IPC_CALLBACK

typedef uint32_t u32;
typedef uint8_t u8;

typedef union {
    struct {
        u32 DW[IPC_COMMON_MSG_LEN_IN_DW];
    };
    struct {
        union {
            struct {
                u32 opcode       : 8;
                u32 sub_opcode   : 8;
                u32 rsvd         : 8;
                u32 flags        : 8;
            };
            struct {
                u32              : 8;
                u32              : 8;
                u32 err          : 8;
                u32 status       : 8;
            };
        } hdr;
        u32 context[6];
        u32 user_tag     : 8;
        u32 dest         : 4;
        u32 source       : 4;
        u32 msg_type     : 2;
        u32 rsvd_footer  : 6;
        u32 check_sum    : 8;
    };
} ipc_common_msg_t;

typedef enum { IPC_OP_SYS_DBG = 3, } ipc_opcode_e;
typedef enum { IPC_SUB_OP_VIRTIO = 0, IPC_SUB_OP_DEBUG, IPC_SUB_OP_FLOW_LOG, IPC_SUB_OP_DST_MAC, IPC_SUB_OP_HASH, IPC_SUB_OP_MAC_PORT_VID, } ipc_sub_opcode_sys_dbg_e;
typedef enum { CPUID_CORE0 = 0, CPUID_CORE1, CPUID_CORE2, CPUID_CORE3, CPUID_MAX, } ipc_cpuid_e;
typedef enum { MSG_REQ = 0, MSG_REP, MAX_MSG_TYPE, } ipc_msg_type_e;

// 假设这些外部函数存在
void ipc_msg_req_hdr_init(ipc_common_msg_t *msg, int op, int sub_op, int flags);
void ipc_msg_common_init(ipc_common_msg_t *msg, int source, int dest, int type, int tag);
int ipc_send_msg(int core_id, ipc_common_msg_t *msg); // 假设成功返回0，失败返回非0
void infra_cli_printf(const char *fmt, ...);
void mac_str_to_bin(const char *mac_str, u8 *bin);
void str2int(const char *str, u32 *val);


/* ========================================================================= */
/* 2. 修正后的分发器和处理器函数                                             */
/* ========================================================================= */

/**
 * @brief 根据命令行参数识别子命令类型
 * @param argc 参数数量
 * @param argv 参数数组
 * @return 对应的命令类型ID，0表示未知命令
 */
static int get_sub_cmd_type(int argc, const char *argv[]) {
    // argv[0] is the command itself, e.g., "sysdbg"
    // argv[1] is the sub-command
    if (argc < 2) {
        return 0;
    }
    
    const char *sub_cmd = argv[1];

    // 使用 strcmp 进行精确匹配
    if (strcmp(sub_cmd, "virtio") == 0) return 1;
    if (strcmp(sub_cmd, "debug") == 0) return 2;
    if (strcmp(sub_cmd, "flow-log") == 0) return 3;

    // 对于带有 "=" 的命令，使用 strncmp 进行前缀匹配
    if (strncmp(sub_cmd, "dstmac=", strlen("dstmac=")) == 0) {
        if (argc == 2) {
            return 4; // 格式: dstmac=...
        }
        // 更健壮地检查复合命令
        if (argc == 4 && 
            strncmp(argv[2], "srcport=", strlen("srcport=")) == 0 && 
            strncmp(argv[3], "vid=", strlen("vid=")) == 0) {
            return 5; // 格式: dstmac=... srcport=... vid=...
        }
    }
    
    if (strncmp(sub_cmd, "hash=", strlen("hash=")) == 0 && argc == 2) {
        return 6; // 格式: hash=...
    }
    
    return 0; // 未知命令
}


static bool sysdbg_virtio(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    if (argc != 5 && argc != 6) {
        return false;
    }
    bool detail = false;
    #ifdef PSW_IPC_CALLBACK
    u8 core    = strtoul(argv[2], NULL, 0);
    u32 devid  = strtoul(argv[3], NULL, 0);
    u32 funid  = strtoul(argv[4], NULL, 0);
    if (argc == 6) {
        detail = (bool)strtoul(argv[5], NULL, 0);
    }
    msg->context[0] = core;
    msg->context[1] = devid;
    msg->context[2] = funid;
    msg->context[3] = detail;
    #else 
    u8 core    = strtoul(argv[2], NULL, 0);
    u32 ufunid = strtoul(argv[3], NULL, 0);
    u8 type    = strtoul(argv[4], NULL, 0);
    if (argc == 6) {
        detail = (bool)strtoul(argv[5], NULL, 0);
    }
    msg->context[0] = core;
    msg->context[1] = ufunid;
    msg->context[2] = type;
    msg->context[3] = detail;
    #endif
    ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_VIRTIO, 0);
    ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
    return ipc_send_msg(CPUID_CORE2, msg) == 0;
}

static bool sysdbg_debug(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    if (argc != 5) {
        return false;
    }
    u32 module = strtoul(argv[2], NULL, 0);
    u8 core = strtoul(argv[3], NULL, 0);
    u32 flag = strtoul(argv[4], NULL, 0);
    msg->context[0] = module;
    msg->context[1] = core;
    msg->context[2] = flag;
    ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_DEBUG, 0);
    ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
    return ipc_send_msg(CPUID_CORE2, msg) == 0;
}

static bool sysdbg_flow_log(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    if (argc != 3) {
        return false;
    }
    u32 sw = strtoul(argv[2], NULL, 0);
    msg->context[0] = sw;
    ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_FLOW_LOG, 0);
    ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
    return ipc_send_msg(CPUID_CORE2, msg) == 0;
}

static bool sysdbg_dstmac(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    if (strlen(argv[1]) != 24) { // "dstmac=" (7) + "XX:XX:..." (17)
        infra_cli_printf("please input correct format, dstmac=xx:xx:xx:xx:xx:xx\n");
        return false;
    }
    u8 *dst_mac = (u8*)msg->context;
    mac_str_to_bin((argv[1] + strlen("dstmac=")), dst_mac);
    ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_DST_MAC, 0);
    ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
    return ipc_send_msg(CPUID_CORE2, msg) == 0;
}

static bool sysdbg_dstmac_srcport_vid(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    if (strlen(argv[1]) != 24) {
        infra_cli_printf("please input correct format, dstmac=xx:xx:xx:xx:xx:xx\n");
        return false;
    }
    u8 *dst_mac = (u8*)msg->context;
    u32 srcport = 0;
    u32 vid = 0;

    mac_str_to_bin((argv[1] + strlen("dstmac=")), dst_mac);
    str2int((argv[2] + strlen("srcport=")), &srcport);
    str2int((argv[3] + strlen("vid=")), &vid);

    msg->context[2] = srcport;
    msg->context[3] = vid;

    ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_MAC_PORT_VID, 0);
    ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
    return ipc_send_msg(CPUID_CORE2, msg) == 0;
}

static bool sysdbg_hash(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    u32 hash = 0;
    str2int((argv[1] + strlen("hash=")), &hash);
    
    if (hash) {
        msg->context[0] = hash;
        ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_HASH, 0);
        ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
        return ipc_send_msg(CPUID_CORE2, msg) == 0;
    }
    
    // 如果 hash 为 0，不发送消息，但命令本身执行成功
    return true; 
}


/* ========================================================================= */
/* 3. 修正后的主函数 (CLI 命令入口)                                          */
/* ========================================================================= */

static int infra_cli_cmd_sys_dbg(int argc, const char *argv[]) {
    ipc_common_msg_t msg;
    bool success = false;

    memset(&msg, 0, sizeof(ipc_common_msg_t));

    // 分发器会处理 argc < 2 的情况，但在这里多一层防护更好
    if (argc < 2) {
        infra_cli_printf("sysdbg: input params error...\r\n");
        return -1;
    }

    int sub_cmd_type = get_sub_cmd_type(argc, argv);

    switch (sub_cmd_type) {
        case 1: success = sysdbg_virtio(&msg, argc, argv); break;
        case 2: success = sysdbg_debug(&msg, argc, argv); break;
        case 3: success = sysdbg_flow_log(&msg, argc, argv); break;
        case 4: success = sysdbg_dstmac(&msg, argc, argv); break;
        case 5: success = sysdbg_dstmac_srcport_vid(&msg, argc, argv); break;
        case 6: success = sysdbg_hash(&msg, argc, argv); break;
        default:
            infra_cli_printf("sysdbg: invalid parameters or command not supported!\r\n");
            success = false;
            break;
    }

    if (!success) {
        infra_cli_printf("sysdbg: command execution failed for [%s]\r\n", argv[1]);
    }

    // 将布尔型的成功/失败，转换为符合常规C函数返回值的 0 (成功) 和 -1 (失败)
    return success ? 0 : -1;
}
