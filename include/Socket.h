/**
 *                             _ooOoo_
 *                            o8888888o
 *                            88" . "88
 *                            (| -_- |)
 *                            O\  =  /O
 *                         ____/`---'\____
 *                       .'  \|       |/  `.
 *                      /  \\|||  :  |||//  \
 *                     /  _||||| -:- |||||-  \
 *                     |   | \\\  -  /// |   |
 *                     |  _|  ''\---/''  |   |
 *                     \  .-\__  `-`  ___/-. /
 *                   ___`. .'  /--.--  `. . ___
 *                ."" '<  `.___\_<|>_/___.'  >'"".
 *               | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *               \  \ `-.   \_ __\ /__ _/   .-` /  /
 *          ======`-.____`-.________/___.-`____.-'======
 *                             `=---='
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *   >  Buddha bless:        Socket.h      NO BUG
 *   >        Author:        A$AP Diablo

 *   >          Mail:        hyp547450291@qq.com
 *   >  Created Time:        Thu 24 May 2018 03:29:10 PM CST
 *    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 **/
 
#ifndef _SOCKET_H
#define _SOCKET_H

#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <string>

typedef struct InetAddress
{ 
    struct sockaddr_in addr_;

    InetAddress(const std::string& host, uint32_t port){
       bzero(&addr_, sizeof(addr_));
        addr_.sin_family = AF_INET;
        addr_.sin_port = htons(port);
        addr_.sin_addr.s_addr = htonl(INADDR_ANY);
    }
}InetAddress; //only to listenAddr

class Socket 
{
public: 
    Socket():fd_(-1){ 
       fd_ = socket(AF_INET, SOCK_STREAM, 0); //IPV4
    }

    ~Socket(){
        close(fd_);
    }
    
    void reUse(){ //set sock reuse
        int on = 1;
        if(setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        {
            // Ku$h::xanax::ERR("Socket::reuse setsockopt error");
            perror("Socket::set socketopt error");
        } 
    }
    void nonBlock(){
        int flags = fcntl(fd_, F_GETFL, NULL) ;
        if(-1 == flags)
        {
            perror("Socket::nonBlock error");
            exit(0);
        }
        flags |= O_NONBLOCK;

        if(-1 == fcntl(fd_, F_SETFL, flags))
        {
            perror("Socket::nonBlock error");
            exit(0);
        }
    } 
    int getFd() const { return fd_; }

    void bind(InetAddress& host){
        if(::bind(fd_, (struct sockaddr*)&(host.addr_), sizeof(host.addr_)) < 0)
            perror("Socket::bind error");
        
    }
    void listen(int size){
        if(::listen(fd_, size) < 0)
            perror("Socket::listen error");
        
    }
    int accept() const {
        struct sockaddr_in clientAddr;
        socklen_t len = sizeof(clientAddr);
        int connfd = ::accept(fd_, (struct sockaddr*)&clientAddr, &len);

        if(connfd < 0)
            perror("Socket::accept error");

        return connfd;
            
    }
private:
    int fd_;
};

class TcpSocket : public Socket 
{
public:
    int create(int af)
    {
   //     return Socket(af);
        return 0;
    }
};

#endif
