FROM alpine
RUN apk add --no-cache \
    nginx \
    bash
COPY ./nginx_files/* /etc/nginx/
#HEALTHCHECK CMD ps -e | grep nginx || exit 777
ENTRYPOINT ["nginx","-g", "daemon off;"]