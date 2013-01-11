#ifndef MY_FW_H
#define MY_FW_H

/* band port sockopt command used struture,
 * copy datum from user space and kernel space*/
typedef struct nf_bandport
{
    /* band protocol, TCP?UDP */
    unsigned short protocol;

    /* band port */
    unsigned short port;
} nf_bandport_t;

typedef struct band_status
{
    /* the ip user to band, 0 is not band */
    unsigned int band_ip;

    /* port to band, {0,0} is not set */
    nf_bandport_t band_port;

    /* whether the ping is band, 0 NO, 1 YES */
    unsigned char bind_ping;
} band_status_t;

#endif // MY_FW_H
