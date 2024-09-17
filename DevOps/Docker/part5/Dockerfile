FROM alpine

RUN apk add --no-cache nginx \
    bash \
    gcc \
    spawn-fcgi \
    fcgi \
    fcgi-dev \
    musl-dev

#RUN adduser -D fcgi && \
#    addgroup fcgi_app
#    adduser fcgi fcgi_app && \
#    chown 
#    
#COPY ./doas.conf /etc/doas.d/doas.conf
COPY ./nginx_files/* /etc/nginx/
RUN mkdir /fcgi_app
COPY ./app_files/* /fcgi_app/
RUN chmod +x /fcgi_app/run_app.sh && \
    chown -R nginx /fcgi_app/


HEALTHCHECK CMD ps -e | grep nginx || exit 777
WORKDIR /fcgi_app
ENTRYPOINT ["/bin/bash", "./run_app.sh"]
USER nginx
#ENTRYPOINT ["/fastcgi_app/run_app.sh"]
#CMD ["nginx","-g", "daemon off;"]
#CMD ["/bin/bash", "/fastcgi_app/run_app.sh
#ENTRYPOINT ["/bin/bash", ""]