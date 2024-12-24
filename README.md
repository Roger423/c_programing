生成SSH密钥（如果还没有的话）：
ssh-keygen -t rsa -b 4096 -C "your_email@example.com"

启动SSH代理并添加密钥：
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_rsa


将SSH公钥添加到GitHub账户： 打开您的公钥文件：
cat ~/.ssh/id_rsa.pub

复制输出的公钥并将其添加到GitHub的SSH keys设置中：
https://github.com/settings/keys


更新远程仓库URL为SSH URL：
git remote set-url origin git@github.com:Roger423/c_programing.git


推送代码：
git push -u origin master
