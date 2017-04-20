//
// Created by danter on 2017-04-20.
//

#ifndef ITIVITI_DEV_SERVERSOCKETIMPL_H
#define ITIVITI_DEV_SERVERSOCKETIMPL_H

class ServerSocketImpl: public IServerSocket {

        void
        Bind(const struct sockaddr *sa, socklen_t salen) override
        {
            if (bind(this->sockfd, sa, salen) < 0)
                throw std::runtime_error(ErrorUtil::err_sys("bind error"));
        }

        void
        Listen(int backlog)
        {
            if (listen(this->sockfd, backlog) < 0)
                throw std::runtime_error(ErrorUtil::err_sys("listen error"));
        }

        int
        Accept(struct sockaddr *sa, socklen_t *salenptr) override
        {
            int n;

            again:
            if ( (n = accept(this->sockfd, sa, salenptr)) < 0) {
                if (errno == EPROTO || errno == ECONNABORTED)
                    goto again;
                else
                    throw std::runtime_error(ErrorUtil::err_sys("accept error"));
            }
            return(n);
        }
};

#endif //ITIVITI_DEV_SERVERSOCKETIMPL_H
