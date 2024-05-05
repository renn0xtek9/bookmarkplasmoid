FROM kdeneon/plasma:developer

COPY install_dependencies_kde_neon_developer.sh /install_dependencies_kde_neon_developer.sh
COPY entrypoint.sh /entrypoint.sh

RUN /install_dependencies_kde_neon_developer.sh

ENTRYPOINT ["/entrypoint.sh"]
