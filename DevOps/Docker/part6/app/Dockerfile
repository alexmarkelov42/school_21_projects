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
RUN chmod +x /fcgi_app/run_app.sh && \
    chown -R nginx /fcgi_app/


HEALTHCHECK CMD ps -e | grep nginx || exit 777
WORKDIR /fcgi_app
ENTRYPOINT ["/bin/bash", "./run_app.sh"]
USER nginx