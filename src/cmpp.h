
/* 
 * China Mobile CMPP 2.0 protocol library
 * By typefo <typefo@qq.com>
 * Update: 2017-07-10
 */

#ifndef _CMPP2_H
#define _CMPP2_H

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define CMPP_VERSION 0x20
#define CMPP_PACK_MAX 4096

/* Cmpp Protocol Port */
#define CMPP_LONG_PORT  7890
#define CMPP_SHORT_PORT 7900

/* Cmpp Protocol Command ID */
#define CMPP_CONNECT                   0x00000001
#define CMPP_CONNECT_RESP              0x80000001
#define CMPP_TERMINATE                 0x00000002
#define CMPP_TERMINATE_RESP            0x80000002
#define CMPP_SUBMIT                    0x00000004
#define CMPP_SUBMIT_RESP               0x80000004
#define CMPP_DELIVER                   0x00000005
#define CMPP_DELIVER_RESP              0x80000005
#define CMPP_QUERY                     0x00000006
#define CMPP_QUERY_RESP                0x80000006
#define CMPP_CANCEL                    0x00000007
#define CMPP_CANCEL_RESP               0x80000007
#define CMPP_ACTIVE_TEST               0x00000008
#define CMPP_ACTIVE_TEST_RESP          0x80000008
#define CMPP_FWD                       0x00000009
#define CMPP_FWD_RESP                  0x80000009
#define CMPP_MT_ROUTE                  0x00000010
#define CMPP_MT_ROUTE_RESP             0x80000010
#define CMPP_MO_ROUTE                  0x00000011
#define CMPP_MO_ROUTE_RESP             0x80000011
#define CMPP_GET_ROUTE                 0x00000012
#define CMPP_GET_ROUTE_RESP            0x80000012
#define CMPP_MT_ROUTE_UPDATE           0x00000013
#define CMPP_MT_ROUTE_UPDATE_RESP      0x80000013
#define CMPP_MO_ROUTE_UPDATE           0x00000014
#define CMPP_MO_ROUTE_UPDATE_RESP      0x80000014
#define CMPP_PUSH_MT_ROUTE_UPDATE      0x00000015
#define CMPP_PUSH_MT_ROUTE_UPDATE_RESP 0x80000015
#define CMPP_PUSH_MO_ROUTE_UPDATE      0x00000016
#define CMPP_PUSH_MO_ROUTE_UPDATE_RESP 0x80000016

/* Error code definition */
#define CMPP_ERR_INITCCS               0xe0000001
#define CMPP_ERR_INITCCTS              0xe0000002
#define CMPP_ERR_INITCBSS              0xe0000003
#define CMPP_ERR_CONUPTL               0xe0000004
#define CMPP_ERR_CONSCPE               0xe0000005
#define CMPP_ERR_CONSRPE               0xe0000006
#define CMPP_ERR_CONPPE                0xe0000007
#define CMPP_ERR_CONISA                0xe0000008
#define CMPP_ERR_CONAF                 0xe0000009
#define CMPP_ERR_CONVITH               0xe0000010
#define CMPP_ERR_CONUNE                0xe0000011
#define CMPP_ERR_ACTSCPE               0xe0000012
#define CMPP_ERR_ACTSRPE               0xe0000013
#define CMPP_ERR_TERSTPE               0xe0000014
#define CMPP_ERR_TERSRPE               0xe0000015
#define CMPP_ERR_SUBSSPE               0xe0000016
#define CMPP_ERR_SUBSRPE               0xe0000017
#define CMPP_ERR_SUBPPE                0xe0000018
#define CMPP_ERR_SUBPCE                0xe0000019
#define CMPP_ERR_SUBMSNR               0xe0000020
#define CMPP_ERR_SUBMLE                0xe0000021
#define CMPP_ERR_SUBTCE                0xe0000022
#define CMPP_ERR_SUBMTL                0xe0000023
#define CMPP_ERR_SUBSCE                0xe0000024
#define CMPP_ERR_SUBBCE                0xe0000025
#define CMPP_ERR_SUBGDNSTBN            0xe0000026
#define CMPP_ERR_SUBISRCID             0xe0000027
#define CMPP_ERR_SUBIMSGSRC            0xe0000028
#define CMPP_ERR_SUBIFTID              0xe0000029
#define CMPP_ERR_SUBIDTID              0xe0000030
#define CMPP_ERR_SUBUNE                0xe0000031

/* Cmpp Packet Message Header */
typedef struct {
	unsigned int totalLength;
    unsigned int commandId;
    unsigned int sequenceId;
} CMPP_HEAD_T;

typedef struct {
    unsigned int totalLength;
    unsigned int commandId;
    unsigned int sequenceId;
    unsigned char data[CMPP_PACK_MAX];
} CMPP_PACK_T;

typedef struct {
    int fd;
    long long conTimeout;
    long long sendTimeout;
    long long recvTimeout;
    pthread_mutex_t rlock;
    pthread_mutex_t wlock;
} CMPP_SOCK_T;

/* Cmpp Session Handle */
typedef struct {
    bool ok;
    char *err;
    CMPP_SOCK_T sock;
    pthread_mutex_t lock;
    unsigned char version;
    unsigned int (*sequence)(void);
} CMPP_SP_T;

/* Cmpp Session Handle */
typedef struct {
    char *err;
    unsigned char version;
    unsigned int (*sequence)(void);
} CMPP_ISMG_T;

extern int cmpp_init_sp(CMPP_SP_T *cmpp, char *host, unsigned short port);
extern int cmpp_init_ismg(CMPP_ISMG_T *cmpp, void *(*kpthread) (void *));
extern int cmpp_connect(CMPP_SP_T *cmpp, const char *user, const char *password);
extern int cmpp_connect_resp(CMPP_SP_T *cmpp);
extern int cmpp_terminate(CMPP_SP_T *cmpp);
extern int cmpp_terminate_resp(CMPP_SP_T *cmpp);
extern int cmpp_submit(CMPP_SP_T *cmpp, const char *phone, const char *message, bool delivery,
                       char *serviceId, char *msgFmt, char *msgSrc);
extern int cmpp_submit_resp(CMPP_SP_T *cmpp);
extern int cmpp_deliver(CMPP_SP_T *cmpp);
extern int cmpp_deliver_resp(CMPP_SP_T *cmpp);
extern int cmpp_active_test(CMPP_SP_T *cmpp);
extern int cmpp_active_test_resp(CMPP_SP_T *cmpp);
extern int cmpp_close(CMPP_SP_T *cmpp);
extern unsigned int gen_sequence(void);
extern bool cmpp_send(CMPP_SP_T *cmpp, void *pack, size_t len);
extern bool cmpp_recv(CMPP_SP_T *cmpp, void *pack, size_t len);
extern int cmpp_submit(CMPP_SP_T *cmpp, const char *phone, const char *message, bool delivery,
                       char *serviceId, char *msgFmt, char *msgSrc);
extern bool is_cmpp_command(void *pack, size_t len, unsigned int command);
extern int cmpp_md5(unsigned char *md, unsigned char *src, unsigned int len);
extern int cmpp_conv(const char *src, size_t slen, char *dst, size_t dlen, const char* fromcode, const char* tocode);

#endif
