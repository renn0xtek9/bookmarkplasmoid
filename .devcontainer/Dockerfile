FROM mcr.microsoft.com/devcontainers/base:focal
COPY install_dependencies.sh /workspaces/install_dependencies.sh

RUN chown -R vscode:vscode /workspaces
USER vscode
ENV USER=vscode
RUN cd /workspaces
RUN /workspaces/install_dependencies.sh
