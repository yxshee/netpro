#!/bin/bash
# Configure FTP Server
sudo apt update
sudo apt install -y vsftpd
sudo cp /etc/vsftpd.conf /etc/vsftpd.conf_default
sudo useradd -m testuser
echo "testuser:password" | sudo chpasswd
sudo ufw allow 20/tcp
sudo ufw allow 21/tcp
sudo systemctl restart vsftpd

# Configure Telnet Server
sudo apt install -y telnetd
sudo systemctl restart inetd

# Configure SSH Server
sudo apt install -y openssh-server
# Change SSH port to 1337
sudo sed -i 's/#Port 22/Port 1337/' /etc/ssh/sshd_config
sudo ufw allow 1337/tcp
sudo systemctl restart sshd
