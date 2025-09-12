
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


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

typedef bool (*sysdbg_cmd_handler_t)(ipc_common_msg_t *msg, int argc, const char *argv[]);

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
    
    return true; 
}

typedef enum {
    CMD_UNKNOWN = 0,
    CMD_VIRTIO,
    CMD_DEBUG,
    CMD_FLOW_LOG,
    CMD_DSTMAC,
    CMD_DSTMAC_PORT_VID,
    CMD_HASH,
    CMD_MAX
} sysdbg_cmd_id_e;

static const sysdbg_cmd_handler_t sysdbg_callbacks[CMD_MAX] = {
    [CMD_UNKNOWN]         = NULL, // 索引0不对应任何有效命令
    [CMD_VIRTIO]          = sysdbg_virtio,
    [CMD_DEBUG]           = sysdbg_debug,
    [CMD_FLOW_LOG]        = sysdbg_flow_log,
    [CMD_DSTMAC]          = sysdbg_dstmac,
    [CMD_DSTMAC_PORT_VID] = sysdbg_dstmac_srcport_vid,
    [CMD_HASH]            = sysdbg_hash,
};

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

static int infra_cli_cmd_sys_dbg(int argc, const char *argv[]) {
    ipc_common_msg_t msg;
    bool success = false;

    memset(&msg, 0, sizeof(ipc_common_msg_t));

    if (argc < 2) {
        infra_cli_printf("sysdbg: input params error...\r\n");
        return -1;
    }

    sysdbg_cmd_id_e cmd_id = get_sysdbg_cmd_id(argc, argv);

    if (cmd_id > CMD_UNKNOWN && cmd_id < CMD_MAX && sysdbg_callbacks[cmd_id] != NULL) {
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

