FROM alpine

RUN apk add --no-cache nginx \
    bash \
    gcc \
    spawn-fcgi \
    fcgi \
    fcgi-dev \
    musl-dev

COPY ./nginx_files/* /etc/nginx/
RUN mkdir /fcgi_app
COPY ./app_files/* /fcgi_app/
RUN chmod +x /fcgi_app/run_app.sh

WORKDIR /fcgi_app
ENTRYPOINT ["/bin/bash", "./run_app.sh"]
#ENTRYPOINT ["/fastcgi_app/run_app.sh"]
#CMD ["nginx","-g", "daemon off;"]
#CMD ["/bin/bash", "/fastcgi_app/run_app.sh
#ENTRYPOINT ["/bin/bash", ""]