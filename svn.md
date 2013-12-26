
##SubVersion


##目录

**SubVersion服务安装设置**

- [简介](#introduction)
- [访问方式](#access_protocol)
	- 直接访问文件仓库(file://)
	- 通过 WebDAV 协议访问(http://)
	- 通过具有安全套接字(SSL)的 WebDAV 协议访问(https:// )
	- 通过自带协议访问(svn://)
	- 通过具被SSH隧道保护的自带协议访问(svn+ssh://)
- [使用笔记](#note)
- [附件：git cmd](#git)
---

<h2 id="introduction">简介</h2>
Subversion 是一款开放源代码的版本控制系统。使用 Subversion， 您可以重新加载源代码和文档的历史版本。 Subversion 管理了源代码在各个时期的版本。一个文件树被集中放置在文件仓库中。这个文件仓库很像是一个传统的文件服务器，只不过它能够记住文件和目录的每一次变化。

---

<h2 id="access_protocol">访问方式</h2>

下表显示了不同的 URL 模式对应的访问方法：

模式|访问方法
:-------|:---------------
file:///|直接访问本地硬盘上文件仓库
http://	|通过 WebDAV 协议访问支持 Subversion 的 Apache 2 Web 服务器
https://|类似 http://，支持 SSL 加密
svn://	|通过自带协议访问 svnserve 服务器
svn+ssh://|类似 svn://，支持通过 SSH 通道


###直接访问文件仓库(file://)

这是所有访问方式中最简单的。它不需要事先运行任何 SVN 服务。这种访问方式用于访问本地的 SVN 文件仓库。
语法是：

	$ svn co file:///home/svn/myproject
	$ svn co file://localhost/home/svn/myproject
注意：如果您并不确定主机的名称，您必须使用三个斜杠(///)，而如果您指定了主机的名称，则您必须使用两个斜杠(//).
对文件仓库的访问权限基于文件系统的权限。如果该用户具有读/写权限，那么他/她就可以签出/提交修改。

###通过 WebDAV 协议访问(http://)

在Ubuntu下使用Apache配置Subversion实现http://协议访问版本库

1.安装必要软件
`$ sudo apt-get install subversion libapache2-svnapache2`

2.修改apache配置文件`/etc/apache2/mods-available/dav_svn.conf`

	mypro<
	DAV svn
	SVNPath /home/svn/mypro
	AuthType Basic
	AuthName "myproject subversion repository"
	AuthUserFile /etc/subversion/passwd
	#Require valid-user
	#

如果需要用户每次登录时都进行用户密码验证，请将后两行注释掉。

3.创建 /etc/subversion/passwd 文件，该文件包含了用户授权的详细信息
`$ sudo htpasswd -c /etc/subversion/passwd user_name`

4.您可以通过下面的命令来访问文件仓库：

	$ svn co http://hostname/svn/myproject myproject --username user_name
	http://hostname/svn/myproject

**警告**：密码是通过纯文本传输的。如果您担心密码泄漏的问题，我们建议您使用 SSL 加密，有关详情请看下一节。


###通过具有安全套接字(SSL)的 WebDAV 协议访问(https:// )
通过具有 SSL 加密的 WebDAV 协议访问 SVN 文件仓库(https:// )非常类似上节所述的内容，为 Apache 2 Web 服务器设置数字证书即可。

###通过自带协议访问(svn://)

配置svnserve实现svn://协议访问版本库

###内置的验证和授权
当客户端连接到一个svnserve进程时，下面的流程就会触发：

- 1)、客户选择一个指定的Repository；
- 2)、服务处理Repository的配置文件 conf/svnserve.conf文件， 并且开始执行在其中定义的所有验证和授权策略；
- 3)、依赖与情形和授权策略：
    - (a)客户端也许允许匿名访问而不需要验证，或者
    - (b)客户端也许需要在任何时候被要求验证，或者
    - (c)假如处于"隧道模式"中，客户端将声明自己已经可以被外部验证。


####访问权限设置
*修改配置文件 `$svnrepo/conf/svnserve.conf`*

	[general] #去掉#[general]前面的#号
	anon-access = none #匿名访问的权限，可以是read,write,none,默认为read
	auth-access = write #认证用户的权限，可以是read,write,none,默认为write
	password-db = passwd #密码数据库的路径，去掉前面的#
	*注意*：所有的行都必须顶格，否则报错。

*修改配置文件passwd*

	[users]
	sxy = sxy
	svnuser = password
	jesszjessz = jessz
	*注意*：
		a. 一定要去掉[users]前面的#,否则svn只能以匿名用户登录
		b. 这里的密码都是没有加密的

####配置SVN xinetd启动方式
在/etc/xinetd.d/下面新建svn文件

	service svn
	{
	disable = no
	port = 3690
	socket_type = stream
	protocol = tcp
	wait = no
	user = svn
	server = /usr/local/bin/svnserve
	server_args = -i -r /home/svn
	}
重启xinetd   /etc/init.d/xinetd restart


####启动SVN服务器

- a).对于单个代码仓库: `svnserve -d -r /home/svn --listen-host 192.168.1.16'

    -d表示在后台运行
    -r指定服务器的根目录
    --listen-host如果服务器有多ip时指定监听的ip地址.

	我们可以在svn客户端中通过svn://192.168.1.16来访问svn服务器
- b).对于多个代码仓库

	用-r选项来指定服务器根目录,访问时需要写上每个仓库相对于svn根目录的相对路径.
	比如,我们有两个代码仓库/home/repo1 和/home/repo2,
	启动：·svnserve -d -r /home--listen-host 192.168.1.16,
	那么在客户端可以用svn://192.168.1.16/repo1和svn://192.168.1.16/repo2来分别访问两个项目

- c).检查是否正常启动
svn默认端口是3690，可以端口为3690的地址是否启动成功
`$ netstat -ntlp |grep 3690`

在防火墙上开放这个端口。

	`/sbin/iptables -A INPUT -i eth0 -p tcp --dport 3690 -j ACCEPT`
	`/sbin/service iptables save`

你也可以通过svnserve的--listen-port 选项来指定一个已经开放的其他端口, 客户端使用时也必须指定端口,如svn://192.168.1.200:9999/.

###通过具被SSH隧道保护的自带协议访问(svn+ssh://)
配置和服务器进程于上节所述相同。我们假设您已经运行了“svnserve”命令。
我们还假设您运行了 ssh 服务并允许接入。要验证这一点，请尝试使用 ssh 登录计算机。如果您可以登录，那么大功告成，如果不能，请在执行下面的步骤前解决它。
svn+ssh:// 协议使用 SSH 加密来访问 SVN 文件仓库。如您所知，数据传输是加密的。要访问这样的文件仓库，请输入：

	$ svn co svn+ssh://hostname/home/svn/myproject myproject --username user_name

注意：在这种方式下，您必须使用完整的路径(/home/svn/myproject)来访问 SVN 文件仓库
基于服务器的配置，它会要求输入密码。您必须输入您用于登录 ssh 的密码，一旦通过验证，就会签出文件仓库中的代码。
您还应该参考 SVN book 以了解关于 svn+ssh:// 协议的详细信息。

****

<h2 id="note">使用笔记</h2>

###svn ignore:

- 若想创建了一个文件夹，并且把它加入版本控制，但忽略文件夹中的所有文件的内容：

	- $ svn mkdir spool
	- $ svn propset svn:ignore '*' spool
	- $ svn ci -m 'Adding "spool" and ignoring its contents.'

- 若想创建一个文件夹，但不加入版本控制，即忽略这个文件夹：

	- $ mkdir spool
	- $ svn propset svn:ignore 'spool' .
	- $ svn ci -m 'Ignoring a directory called "spool".'

- 若已经创建了文件夹，并加入了版本控制，现在想忽略这个文件夹，但要保持文件夹的内容：

	- $ svn export spool spool-tmp
	- $ svn rm spool
	- $ svn ci -m 'Removing inadvertently added directory "spool".'
	- $ mv spool-tmp spool
	- $ svn propset svn:ignore 'spool' .
	- $ svn ci -m 'Ignoring a directory called "spool".'

----

###SVN常用命令

命令 | 含义
:---------------------- |:------------------------
svn checkout URL[@REV]... [PATH] |将文件checkout到本地目录
svn add file |往版本库中添加新的文件
svn commit -m “LogMessage” [-N] PATH |将改动的文件提交到版本库
svn lock -m “LockMessage” [--force] PATH |加锁
svn unlock PATH |解锁
svn update -r m path |更新到某个版本
svn status path |查看文件或者目录状态
svn delete path -m “delete test fle” |删除文件
svn log path |查看日志
svn info path |查看文件详细信息
svn diff path |将修改的文件与基础版本比较
svn diff -r m:n path |对版本m和版本n比较差异
svn merge -r m:n path |将两个版本之间的差异合并到当前文件
svn help [cmd] |SVN 帮助


###SVN不常用命令

命令 | 含义
:---------------------- |:------------------------
svn list path    |版本库下的文件和目录列表
svn ls |显示path目录下的所有属于版本库的文件和目录简写
svn mkdir  |创建纳入版本控制下的新目录。
svn revert |恢复原始未改变的工作副本文件 
svn switch (sw) |更新工作副本至不同的URL。
svn switch URL [PATH] | 将工作副本，映射到一个新的URL，并将服务器上文件与本地文件合并。
svn switch --relocate FROM TO [PATH...] | 写工作副本的URL元数据，以反映单纯的仓库的URL上的改变。
svn resolved |移除工作副本的目录或文件的“冲突”状态。
svn cat 目标[@版本]... | 输出指定文件或URL的内容。
svn cleanup | 搜索工作副本并执行所有遗留的日志，在这过程中删除锁。
svn import | 把未版本化的文件树复制到资料库

###SVN实例

- 删除目录下所有的 .svn 隐藏子目录

	find . -name ".svn" -print0 | xargs -0 rm -rf


- tags打分支

	svn  cp  trunk/    tags/platform_2011.11.11 
	svn  ci  -m  "svn  cp  trunk/    tags/platform_2011.11.11"

- svn 改名

	svn  mv  platform_2011.11.11   platform_20111111
	svn  ci  -m  "svn  mv  platform_2011.11.11   platform_20111111"        // 提交

- fix svn directory is missing

	1） svn up missingDirName
	2） svn del missingDirName
	3） svn ci

- svn chech version

	svn  co  http://192.168.1.100/platform/branch  -r  12  platform_branch_v12

- svn log

	svn  log  http://192.168.1.100/platform/branch  -l10 // svn  文字注释log
	svn  log  http://192.168.1.100/platform/branch  -l10  -v // svn 文字注释log + 文件更新log（增，删，改）

- svn diff 

    svn diff -r  v_1 : v_2 svn_path
	svn diff -r 200:201 test.php

- 查看svn版本

	svnserve --version

- ubuntu 安装svn 1.7、1.8

	当前 ubuntu 12.04 中的 svn 版本为 1.6，这个版本会在每个子目录新建一个.svn 的目录保存版本文件，很不爽。找到一个第三方编译的 ubuntu 源：

	sudo vi /etc/apt/sources.list
	add:
	deb http://ppa.launchpad.net/dominik-stadler/subversion-1.7/ubuntu precise main
	deb-src http://ppa.launchpad.net/dominik-stadler/subversion-1.7/ubuntu precise main

	sudo apt-get install subversion

****

<h2 id="git">附件：git cmd</h2>

###git 中的常量

常量名 | 含义
:---------- | :-----------
HEAD&#94; | 最近一次的commit
HEAD&#94;&#94; | HEAD父母的信息
HEAD~4 | HEAD父母的父母的信息
HEAD&#94;1 | HEAD的第一个父母的信息
HEAD&#94;2 | HEAD的第二个父母的信息
COMMIT_EDITMSG | 最后一次commit时的提交信息
MERGE_HEAD | 如果是merge产生的commit，那么它表示除HEAD之外的另一个父母分支。
FETCH_HEAD | 使用git-fetch获得的object和ref的信息都存储在这里，这些信息是为日后git-merge准备的。

###git 的基本命令

基本命令 | 含义
:-------------- | :------------
git help command | 查看帮助
git command --help |查看帮助
git config --global user.name \<username\> | 设置用户名
git config --global user.email \<email\>  | 设置用户邮箱
git config --list | 查看用户信息
git init | 初始化
git clone /path/to/repository | 创建一个本地仓库的克隆
<span style="white-space:nowrap">git clone username@host:/path/to/repository</span> | 创建一个远端服务器仓库的克隆
git add \<filename\> | 将改动添加到缓存区
git add * | 将改动添加到缓存区
git commit -m "代码提交信息" | 提交改动
git commit --amend -m "新的提交信息" | 提交改动（若有改动） + 修补最近一次提交
git push origin master | 这些改动提交到远端仓库master分支
git remote add origin \<server\> | 修改推送到远程的服务器
git checkout -b feature_x | 创建一个叫做“feature_x”的分支，并切换过去
git checkout master | 切换回主分支
git branch -d feature_x | 删除分支
git pull | 更新本地仓库至最新
git merge \<branch\> | 合并其他分支到当前分支
git diff \<source_branch\> \<target_branch\> | 查看分支间差异
git log | 获取提交 ID
git tag 1.0.0 \<ID\> | 创建一个叫做 1.0.0 的标签
git checkout -- \<filename\> | 用git仓库的HEAD替换当前工作目录的改动


###git 命令详解

命令 | 含义
:-------------- | :------------
**git add 命令** | 
git add file_name       |加单个文件
git add .          |加当前目录的所有文件
git add -i |进入交互式add
git add -p |直接进入补丁模式，可以暂存修改的一部分。
**git commit 命令** |
git commit -a | 第一步：自动地add所有改动的代码，使得所有的开发代码都列于index file中；第二步：自动地删除那些在index file中但不在工作树中的文件；第三步：执行commit命令来提交。
**git push 命令** | 
git push origin test:test2 |提交本地test分支作为远程test2分支
git push origin test |提交本地test分支作为远程test分支
git push origin :test |删除远程test分支
git push origin :refs/tags/t4 |删除远程tag标签t4
**git pull 命令** | 
git pull origin test:test2 |取回远程的test分支作为本地的test2分支
**git checkout 命令** | 
git checkout test |如果本地无test分支，先需要从远程pull回test分支
**git branch 命令** | 
git branch b4 t4 |以tag t4建立新的分支b4
**git merge 命令** | 
git merge AAA      |将分支AAA与当前分枝合并
**git diff&nbsp;命令** | 
git diff&nbsp; |查看working tree与index file的差别的（这个命令只在git add之前使用有效。如果已经add了，那么此命令输出为空）。
<span style="white-space:nowrap">git diff --cached</span> |查看index file与commit的差别的（这个命令在git add之后在git commit之前有效。）。
git&nbsp;diff&nbsp;HEAD |查看working tree和commit的差别的。（你一定没有忘记，HEAD代表的是最近的一次commit的信息）
**git reset 命令** | 
git reset --soft |只撤销commit，保留working tree和index file。
<span style="white-space:nowrap">git reset --mixed</span> |撤销commit和index file，保留working tree
git reset --hard |撤销commit、index file和working tree，即撤销销毁最近一次的commit
git reset |和git reset --mixed完全一样
git reset -- |用于删除登记在index file里的某个文件。例如：git reset -- roc.c
**git revert 命令** | 
git revert |用于回滚（撤销）一些commit。对于一个或者多个已经存在的commit，去除由这些commit引入的改变，并且用一个新的commit来记录这个回滚操作。这个命令要求working tree必须是干净的。
git revert HEAD~3 |丢弃最近的三个commit，把状态恢复到最近的第四个commit，并且提交一个新的commit来记录这次改变。
<span style="white-space:nowrap">git revert -n master~5..master~2</span> |丢弃从最近的第五个commit（包含）到第二个（不包含）,但是不自动生成commit，这个revert仅仅修改working tree和index。
**git rebase** |
**git submodule** | （1、2）



## 应用实例

###git中修改commit的message的方法
- git rebase -i master~5
- 这个是找出master分支最近5次的commit，看见那个写错的了吧？把pick改成reword

###丢弃你所有的本地改动与提交
- 到服务器上获取最新的版本并将你本地主分支指向到它
  1. git fetch origin
  2. git reset --hard origin/master

[Git常用命令备忘](http://robbinfan.com/blog/34/git-common-command)
[Git简易指南](http://rogerdudler.GitHub.com/git-guide/index.zh.html)
[Linux大棚的Git教程](http://roclinux.cn/?tag=git)
[GIT基本概念和用法总结](http://guibin.iteye.com/blog/1014369)
[Git分支管理策略](http://www.ruanyifeng.com/blog/2012/07/git.html)
[Git初學筆記](http://blog.longwin.com.tw/2009/05/git-learn-initial-command-2009/)
[Git Magic](http://www-cs-students.stanford.edu/~blynn/gitmagic/intl/zh_cn/)
[GetGitHub](http://www.worldhello.net/gotgithub/index.html)
[git reset --hard和git revert命令](http://blog.sina.com.cn/s/blog_68af3f090100rp5r.html)
[Git-rebase 小筆記](http://blog.yorkxin.org/2011/07/29/git-rebase)
[版本控制系統 Git 精要](http://ihower.tw/git/)
