FROM mcr.microsoft.com/devcontainers/base:jammy
COPY install_dependencies_ubuntu_22.sh /workspaces/install_dependencies_ubuntu_22.sh
COPY .gdbinit /home/vscode/.gdbinit
RUN /workspaces/install_dependencies_ubuntu_22.sh
