
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


#define IPC_COMMON_MSG_LEN_IN_DW		(8)
#define PSW_IPC_CALLBACK


typedef uint32_t u32;
typedef uint8_t u8;

typedef union {
    struct {
        u32 DW[IPC_COMMON_MSG_LEN_IN_DW];
    };
    struct {              // Common structure
        union {
            struct {
                u32 opcode 	     : 8;
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
        u32 user_tag         : 8;
        u32 dest             : 4;  // IPC_MODULE_ID_E destination module ID
        u32 source           : 4;  // IPC_MODULE_ID_E source module ID
        u32 msg_type         : 2;  // IPC_MSG_TYPE_E
        u32 rsvd             : 6;  // Reserved for future use
        u32 check_sum        : 8;  // for internal FIFO check
    };
} ipc_common_msg_t;

typedef enum {
	IPC_OP_PSW_FWSTATE = 0,
	IPC_OP_VNET_FWSTATE,
	IPC_OP_VBLK_FWSTATE,
	IPC_OP_SYS_DBG,
	IPC_OP_RDMA_FWSTATE,
	IPC_OP_RDMA_QP_CTX,
} ipc_opcode_e;

typedef enum {
	IPC_SUB_OP_VIRTIO = 0,
	IPC_SUB_OP_DEBUG,
	IPC_SUB_OP_FLOW_LOG,
	IPC_SUB_OP_DST_MAC,
	IPC_SUB_OP_HASH,
	IPC_SUB_OP_MAC_PORT_VID,
} ipc_sub_opcode_sys_dbg_e;

typedef enum {
    CPUID_CORE0 = 0,
    CPUID_CORE1,
    CPUID_CORE2,
    CPUID_CORE3,
    CPUID_MAX,
} ipc_cpuid_e;

typedef enum {
    MSG_REQ = 0,
    MSG_REP,
    MAX_MSG_TYPE,
} ipc_msg_type_e;

void ipc_msg_req_hdr_init(ipc_common_msg_t *msg,
    u8 opcode, u8 sub_opcode, u8 flags)
{
    msg->hdr.opcode = opcode;
    msg->hdr.sub_opcode = sub_opcode;
    msg->hdr.flags = flags;
}

void ipc_msg_common_init(ipc_common_msg_t *msg,
    ipc_cpuid_e source, ipc_cpuid_e dst,
    ipc_msg_type_e msg_type, u8 user_tag)
{
    msg->source = source;
    msg->dest = dst;
    msg->msg_type = msg_type;
    msg->user_tag = user_tag;
}

extern bool ipc_send_msg(ipc_cpuid_e cid, ipc_common_msg_t *msg);

int get_sub_cmd_type(char *sub_cmd[], int sub_cmd_len, int arg_count)
{
	if (!strncmp(sub_cmd, "virtio", sub_cmd_len + 1)) return 1;
	else if (!strncmp(sub_cmd, "debug", sub_cmd_len+1)) return 2;
	else if (!strncmp(sub_cmd, "flow-log", sub_cmd_len+1)) return 3;
	else if (!strncmp(sub_cmd, "dstmac=", sub_cmd_len+1) && (arg_count == 2)) return 4;
	else if (!strncmp(sub_cmd, "dstmac=", sub_cmd_len+1) && (arg_count == 4)) return 5;
	else if (!strncmp(sub_cmd, "hash=", sub_cmd_len+1) && (arg_count == 2)) return 6;
	return 0;
}

bool sysdbg_virtio(ipc_common_msg_t *msg, int argc, const char *argv[])
{
	if (5 != argc && 6 != argc) {
		return false;
	}
	bool detail = false;
	#ifdef PSW_IPC_CALLBACK
	u8 core    = strtoul(argv[2], NULL, 0);
	u32 devid  = strtoul(argv[3], NULL, 0);
	u32 funid  = strtoul(argv[4], NULL, 0);
	if (6 == argc) {
		detail = strtoul(argv[5], NULL, 0);
	}
	#else 
	u8 core    = strtoul(argv[2], NULL, 0);
	u32 ufunid = strtoul(argv[3], NULL, 0);
	u8 type    = strtoul(argv[4], NULL, 0);
	if (6 == argc) {
		detail = strtoul(argv[5], NULL, 0);
	}
	#endif
	#ifdef PSW_IPC_CALLBACK
	msg->context[0] = core;
	msg->context[1] = devid;
	msg->context[2] = funid;
	msg->context[3] = detail;
	#else
	msg.context[0] = core;
	msg.context[1] = ufunid;
	msg.context[2] = type;
	msg.context[3] = detail;
	#endif
	ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_VIRTIO, 0);
	ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
	return !ipc_send_msg(CPUID_CORE2, msg);
}

bool sysdbg_debug(ipc_common_msg_t *msg, int argc, const char *argv[])
{
	if (5 != argc) {
		return -1;
	}
	u32 module = strtoul(argv[2], NULL, 0);
	u8 core = strtoul(argv[3], NULL, 0);
	u32 flag = strtoul(argv[4], NULL, 0);
	msg->context[0] = module;
	msg->context[1] = core;
	msg->context[2] = flag;
	ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_DEBUG, 0);
	ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
	return !ipc_send_msg(CPUID_CORE2, msg);
}

bool sysdbg_flow_log(ipc_common_msg_t *msg, int argc, const char *argv[])
{
	u32 sw = strtoul(argv[2], NULL, 0);
	msg->context[0] = sw;
	ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_FLOW_LOG, 0);
	ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
	return !ipc_send_msg(CPUID_CORE2, msg);
}

bool sysdbg_dstmac(ipc_common_msg_t *msg, int argc, const char *argv[])
{
	printf("%d,%s,%s\n",argc,argv[0],argv[1]);
	if(24 != (int)strlen(argv[1])){
		infra_cli_printf("please input correct format, dstmac=xx:xx:xx:xx:xx:xx\n");
		return -1;
	}
	// printf("len is %d\n",(int)strlen(argv[1]));
	u8 *dst_mac = (u8*)msg->context;
	mac_str_to_bin((argv[1] + strlen("dstmac=")), dst_mac);
	// printf("dstmac is %02x:%02x:%02x:%02x:%02x:%02x\n",dst_mac[0],dst_mac[1],dst_mac[2],dst_mac[3],dst_mac[4],dst_mac[5]);
	ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_DST_MAC, 0);
	ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
	return !ipc_send_msg(CPUID_CORE2, msg);
}

bool sysdbg_dstmac_srcport_vid(ipc_common_msg_t *msg, int argc, const char *argv[])
{
	if ((!strncmp(argv[2], "srcport=", strlen("srcport="))) && (!strncmp(argv[3], "vid=", strlen("vid=")))) {
		printf("%d,%s,%s,%s,%s\n",argc,argv[0],argv[1],argv[2],argv[3]);
		u8 *dst_mac = (u8*)msg->context;
		u32 srcport = 0;
		u32 vid = 0;
		if(24 != (int)strlen(argv[1])){
			infra_cli_printf("please input correct format, dstmac=xx:xx:xx:xx:xx:xx\n");
			return -1;
		}
		mac_str_to_bin((argv[1] + strlen("dstmac=")), dst_mac);
		str2int((argv[2] + strlen("srcport=")), &srcport);
		str2int((argv[3] + strlen("vid=")), &vid);
		msg->context[2] = srcport;
		msg->context[3] = vid;
		ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_MAC_PORT_VID, 0);
		ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
		return !ipc_send_msg(CPUID_CORE2, msg);
	}
}

bool sysdbg_hash(ipc_common_msg_t *msg, int argc, const char *argv[])
{
	printf("%d,%s,%s\n",argc,argv[0],argv[1]);
	u32 hash = 0;
	str2int((argv[1] + strlen("hash=")), &hash);
	msg->context[0] = hash;
	if (hash) {
		ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_HASH, 0);
		ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
		return !ipc_send_msg(CPUID_CORE2, msg);
	}
}

static bool infra_cli_cmd_sys_dbg(int argc, const char *argv[])
{
	ipc_common_msg_t msg;
	memset(&msg, 0, sizeof(ipc_common_msg_t));

	if (1 >= argc) {
		infra_cli_printf("sysdbg: input params error...\r\n");
		return false;
	}

	int sub_cmd_type = get_sub_cmd_type(argv[1], strlen(argv[1]), argc);

	switch (sub_cmd_type)
	{
	case 1:
		return sysdbg_virtio(&msg, argc, argv);
	case 2:
		return sysdbg_debug(&msg, argc, argv);
	case 3:
		return sysdbg_flow_log(&msg, argc, argv);
	case 4:
		return sysdbg_dstmac(&msg, argc, argv);
	case 5:
		return sysdbg_dstmac_srcport_vid(&msg, argc, argv);
	case 6:
		return sysdbg_hash(&msg, argc, argv);
	default:
		infra_cli_printf("sysdbg: invalid parameters!\r\n");
		return false;
	}
}








static int infra_cli_cmd_sys_dbg(int argc, const char *argv[])
{
	ipc_common_msg_t msg;
	int ret;

	memset(&msg, 0, sizeof(ipc_common_msg_t));

	if (1 >= argc) {
		infra_cli_printf("sysdbg: input params error...\r\n");
		return -1;
	}
	if (!strncmp(argv[1], "virtio", strlen("virtio")+1)) {
		if (5 != argc && 6 != argc) {
			return -1;
		}
		bool detail = false;
		#ifdef PSW_IPC_CALLBACK
		u8 core    = strtoul(argv[2], NULL, 0);
		u32 devid  = strtoul(argv[3], NULL, 0);
		u32 funid  = strtoul(argv[4], NULL, 0);
		if (6 == argc) {
			detail = strtoul(argv[5], NULL, 0);
		}
		#else 
		u8 core    = strtoul(argv[2], NULL, 0);
		u32 ufunid = strtoul(argv[3], NULL, 0);
		u8 type    = strtoul(argv[4], NULL, 0);
		if (6 == argc) {
			detail = strtoul(argv[5], NULL, 0);
		}
		#endif
		#ifdef PSW_IPC_CALLBACK
		msg.context[0] = core;
		msg.context[1] = devid;
		msg.context[2] = funid;
		msg.context[3] = detail;
		#else
		msg.context[0] = core;
		msg.context[1] = ufunid;
		msg.context[2] = type;
		msg.context[3] = detail;
		#endif
		ipc_msg_req_hdr_init(&msg, IPC_OP_SYS_DBG, IPC_SUB_OP_VIRTIO, 0);
		ipc_msg_common_init(&msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
		ret = !ipc_send_msg(CPUID_CORE2, &msg);
	} else if (!strncmp(argv[1], "debug", strlen("debug")+1)) {
		if (5 != argc) {
			return -1;
		}
		u32 module = strtoul(argv[2], NULL, 0);
		u8 core = strtoul(argv[3], NULL, 0);
		u32 flag = strtoul(argv[4], NULL, 0);
		msg.context[0] = module;
		msg.context[1] = core;
		msg.context[2] = flag;
		ipc_msg_req_hdr_init(&msg, IPC_OP_SYS_DBG, IPC_SUB_OP_DEBUG, 0);
		ipc_msg_common_init(&msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
		ret = !ipc_send_msg(CPUID_CORE2, &msg);
	} else if (!strncmp(argv[1], "flow-log", strlen("flow-log")+1)) {
		u32 sw = strtoul(argv[2], NULL, 0);
		msg.context[0] = sw;
		ipc_msg_req_hdr_init(&msg, IPC_OP_SYS_DBG, IPC_SUB_OP_FLOW_LOG, 0);
		ipc_msg_common_init(&msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
		ret = !ipc_send_msg(CPUID_CORE2, &msg);
	} else if (!strncmp(argv[1], "dstmac=", strlen("dstmac=")) && (argc == 2)) {
		printf("%d,%s,%s\n",argc,argv[0],argv[1]);
		if(24 != (int)strlen(argv[1])){
			infra_cli_printf("please input correct format, dstmac=xx:xx:xx:xx:xx:xx\n");
			return -1;
		}
		// printf("len is %d\n",(int)strlen(argv[1]));
		u8 *dst_mac = (u8*)msg.context;
		mac_str_to_bin((argv[1] + strlen("dstmac=")), dst_mac);
		// printf("dstmac is %02x:%02x:%02x:%02x:%02x:%02x\n",dst_mac[0],dst_mac[1],dst_mac[2],dst_mac[3],dst_mac[4],dst_mac[5]);
		ipc_msg_req_hdr_init(&msg, IPC_OP_SYS_DBG, IPC_SUB_OP_DST_MAC, 0);
		ipc_msg_common_init(&msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
		ret = !ipc_send_msg(CPUID_CORE2, &msg);
	} else if (!strncmp(argv[1], "hash=", strlen("hash=")) && (argc == 2)) {
		printf("%d,%s,%s\n",argc,argv[0],argv[1]);
		u32 hash = 0;
		str2int((argv[1] + strlen("hash=")), &hash);
		msg.context[0] = hash;
		if (hash) {
			ipc_msg_req_hdr_init(&msg, IPC_OP_SYS_DBG, IPC_SUB_OP_HASH, 0);
			ipc_msg_common_init(&msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
			ret = !ipc_send_msg(CPUID_CORE2, &msg);
		}
	} else if ((!strncmp(argv[1], "dstmac=", strlen("dstmac="))) && (!strncmp(argv[2], "srcport=", strlen("srcport="))) &&(!strncmp(argv[3], "vid=", strlen("vid=")))) {
		printf("%d,%s,%s,%s,%s\n",argc,argv[0],argv[1],argv[2],argv[3]);
		u8 *dst_mac = (u8*)msg.context;
		u32 srcport = 0;
		u32 vid = 0;
		if(24 != (int)strlen(argv[1])){
			infra_cli_printf("please input correct format, dstmac=xx:xx:xx:xx:xx:xx\n");
			return -1;
		}
		mac_str_to_bin((argv[1] + strlen("dstmac=")), dst_mac);
		str2int((argv[2] + strlen("srcport=")), &srcport);
		str2int((argv[3] + strlen("vid=")), &vid);
		msg.context[2] = srcport;
		msg.context[3] = vid;
		ipc_msg_req_hdr_init(&msg, IPC_OP_SYS_DBG, IPC_SUB_OP_MAC_PORT_VID, 0);
		ipc_msg_common_init(&msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
		ret = !ipc_send_msg(CPUID_CORE2, &msg);
	} else {
		infra_cli_printf("cmd[%s] not support\r\n", argv[1]);
	}

	return 0;
}




// 修正后的分发器函数
// 增加了对 argv 的访问，使其能更健壮地判断复合命令
int get_sub_cmd_type(int argc, const char *argv[]) {
    // 基本的参数检查
    if (argc < 2) return 0;
    
    const char *sub_cmd = argv[1];

    if (!strncmp(sub_cmd, "virtio", strlen("virtio") + 1)) return 1;
    if (!strncmp(sub_cmd, "debug", strlen("debug") + 1)) return 2;
    if (!strncmp(sub_cmd, "flow-log", strlen("flow-log") + 1)) return 3;

    // 对于 dstmac，根据 argc 区分两种情况
    if (!strncmp(sub_cmd, "dstmac=", strlen("dstmac="))) {
        if (argc == 2) return 4; // dstmac=...
        // 更健壮的复合命令检查
        if (argc == 4 && !strncmp(argv[2], "srcport=", strlen("srcport=")) 
                      && !strncmp(argv[3], "vid=", strlen("vid="))) {
            return 5; // dstmac=... srcport=... vid=...
        }
    }
    
    if (!strncmp(sub_cmd, "hash=", strlen("hash=")) && (argc == 2)) return 6;
    
    return 0; // 0 代表未知命令
}

// 注意 msg-> 的使用
bool sysdbg_virtio(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    if (5 != argc && 6 != argc) {
        return false;
    }
	bool detail = false;
	#ifdef PSW_IPC_CALLBACK
	u8 core    = strtoul(argv[2], NULL, 0);
	u32 devid  = strtoul(argv[3], NULL, 0);
	u32 funid  = strtoul(argv[4], NULL, 0);
	if (6 == argc) {
		detail = strtoul(argv[5], NULL, 0);
	}
	#else 
	u8 core    = strtoul(argv[2], NULL, 0);
	u32 ufunid = strtoul(argv[3], NULL, 0);
	u8 type    = strtoul(argv[4], NULL, 0);
	if (6 == argc) {
		detail = strtoul(argv[5], NULL, 0);
	}
	#endif
	#ifdef PSW_IPC_CALLBACK
	msg->context[0] = core;
	msg->context[1] = devid;
	msg->context[2] = funid;
	msg->context[3] = detail;
	#else
	msg.context[0] = core;
	msg.context[1] = ufunid;
	msg.context[2] = type;
	msg.context[3] = detail;
	#endif
    ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_VIRTIO, 0);
    ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
    return ipc_send_msg(CPUID_CORE2, msg) == 0; // 假设ipc_send_msg成功返回0
}

// bool sysdbg_virtio(ipc_common_msg_t *msg, int argc, const char *argv[])
// {
// 	if (5 != argc && 6 != argc) {
// 		return false;
// 	}
// 	bool detail = false;
// 	#ifdef PSW_IPC_CALLBACK
// 	u8 core    = strtoul(argv[2], NULL, 0);
// 	u32 devid  = strtoul(argv[3], NULL, 0);
// 	u32 funid  = strtoul(argv[4], NULL, 0);
// 	if (6 == argc) {
// 		detail = strtoul(argv[5], NULL, 0);
// 	}
// 	#else 
// 	u8 core    = strtoul(argv[2], NULL, 0);
// 	u32 ufunid = strtoul(argv[3], NULL, 0);
// 	u8 type    = strtoul(argv[4], NULL, 0);
// 	if (6 == argc) {
// 		detail = strtoul(argv[5], NULL, 0);
// 	}
// 	#endif
// 	#ifdef PSW_IPC_CALLBACK
// 	msg->context[0] = core;
// 	msg->context[1] = devid;
// 	msg->context[2] = funid;
// 	msg->context[3] = detail;
// 	#else
// 	msg.context[0] = core;
// 	msg.context[1] = ufunid;
// 	msg.context[2] = type;
// 	msg.context[3] = detail;
// 	#endif
// 	ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_VIRTIO, 0);
// 	ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
// 	return !ipc_send_msg(CPUID_CORE2, msg);
// }

// 注意返回 false
bool sysdbg_debug(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    if (5 != argc) {
        return false; // 返回 false
    }
    // ... (其余逻辑正确) ...
    return ipc_send_msg(CPUID_CORE2, msg) == 0;
}

// ... sysdbg_flow_log 类似 ...

// 注意返回 false
bool sysdbg_dstmac(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    if (24 != (int)strlen(argv[1])) {
        infra_cli_printf("please input correct format, dstmac=xx:xx:xx:xx:xx:xx\n");
        return false; // 返回 false
    }
    // ... (其余逻辑正确) ...
    return ipc_send_msg(CPUID_CORE2, msg) == 0;
}

// 移除了多余的检查，并修复了返回值问题
bool sysdbg_dstmac_srcport_vid(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    // 分发器已经保证了命令格式，这里的检查可以简化或移除
    if (24 != (int)strlen(argv[1])) {
        infra_cli_printf("please input correct format, dstmac=xx:xx:xx:xx:xx:xx\n");
        return false; // 返回 false
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

// 修复了缺少返回值的BUG
bool sysdbg_hash(ipc_common_msg_t *msg, int argc, const char *argv[]) {
    u32 hash = 0;
    str2int((argv[1] + strlen("hash=")), &hash);
    msg->context[0] = hash;
    
    if (hash) {
        ipc_msg_req_hdr_init(msg, IPC_OP_SYS_DBG, IPC_SUB_OP_HASH, 0);
        ipc_msg_common_init(msg, CPUID_CORE0, CPUID_CORE2, MSG_REQ, 0);
        return ipc_send_msg(CPUID_CORE2, msg) == 0;
    }
    
    return true; // 如果 hash 为 0，不发送消息，但命令本身是成功的
}


// 修正后的主函数
static int infra_cli_cmd_sys_dbg(int argc, const char *argv[]) {
    ipc_common_msg_t msg;
    bool success = false;
    memset(&msg, 0, sizeof(ipc_common_msg_t));

    if (argc < 2) {
        infra_cli_printf("sysdbg: input params error...\r\n");
        return -1; // 保持原始的int返回类型
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
            infra_cli_printf("sysdbg: invalid parameters or command not support!\r\n");
            success = false;
            break;
    }
    
    return success ? 0 : -1; // 将 bool 结果转换为原始的 int 返回值
}
