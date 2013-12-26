
##SubVersion


###目录

**SubVersion服务安装设置**

- [简介](#introduction)
- [访问方式](#access_protocol)
	- 直接访问文件仓库(file://)
	- 通过 WebDAV 协议访问(http://)
	- 通过具有安全套接字(SSL)的 WebDAV 协议访问(https:// )
	- 通过自带协议访问(svn://)
	- 通过具被SSH隧道保护的自带协议访问(svn+ssh://)
- [参考资料](#)
---

<h2 id="introduction">简介</h2>
Subversion 是一款开放源代码的版本控制系统。使用 Subversion， 您可以重新加载源代码和文档的历史版本。 Subversion 管理了源代码在各个时期的版本。一个文件树被集中放置在文件仓库中。这个文件仓库很像是一个传统的文件服务器，只不过它能够记住文件和目录的每一次变化。


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
要通过 WebDAV 协议访问 SVN 文件仓库，必须配置您的 Apache 2 Web 服务器。您必须加入下面的代码片段到您的 `/etc/apache2/mods-available/dav_svn.conf`中：

	DAV svnSVNPath /home/svn/myprojectAuthType 
	BasicAuthName "myproject subversion repository"
	AuthUserFile /etc/subversion/passwd
	#Require valid-user#

接下来，您需要创建 /etc/subversion/passwd 文件，该文件包含了用户授权的详细信息。要添加用户，您可以执行下面的命令：

	`sudo htpasswd -c /etc/subversion/passwd user_name`

它会提示您输入密码，当您输入了密码，该用户就建立了。“-c”选项表示创建新的/etc/subversion/passwd文件，所以`user_name`所指的用户将是文件中唯一的用户。如果要添加其他用户，则去掉“-c”选项即可：

	`sudo htpasswd /etc/subversion/passwd other_user_name`

您可以通过下面的命令来访问文件仓库：

	$ svn co http://hostname/svn/myproject myproject --username user_name

它会提示您输入密码。您必须输入您使用 htpasswd 设置的密码。当通过验证，项目的文件就被签出了。
警告：密码是通过纯文本传输的。如果您担心密码泄漏的问题，我们建议您使用 SSL 加密，有关详情请看下一节。

###通过具有安全套接字(SSL)的 WebDAV 协议访问(https:// )
通过具有 SSL 加密的 WebDAV 协议访问 SVN 文件仓库(https:// )非常类似上节所述的内容，除了您必须为您的 Apache 2 Web 服务器设置数字证书之外。
我们假设您已经为 Apache 2 Web 服务器安装和配置好了相应的数字证书。现在按照上一节所描述的方法访问 SVN 文件仓库，别忘了把 http:// 换成 https://。如何，几乎是一模一样的！

###通过自带协议访问(svn://)
当您创建了 SVN 文件仓库，您可以修改 /home/svn/myproject/conf/svnserve.conf 来配置其访问控制。

例如，您可以取消下面的注释符号来设置授权机制：

	# [general]# password-db = passwd

现在，您可以在“passwd”文件中维护用户清单。编辑同一目录下“passwd”文件，添加新用户。语法如下：
username = password＃(注意行开始不要有多余空格)

现在，您可以在本地或者远程通过 svn://访问 SVN 了，您可以使用“svnserve”来运行 svnserver，语法如下：

	$ sudo svnserve -d --foreground -r /home/svn
	# -d :- daemon mode
	# --foreground :- run in foreground (useful for debugging)
	# -r :- root of directory to serve

要了解更多信息，请输入：$ svnserve --help
当您执行了该命令，SVN 就开始监听默认的端口(3690)。

您可以通过下面的命令来访问文件仓库：
`$ svn co svn://hostname/myproject myproject --username user_name`
基于服务器的配置，它会要求输入密码。一旦通过验证，就会签出文件仓库中的代码。

要同步文件仓库和本地的副本，您可以执行 update 子命令，语法如下：
`$ cd project_dir$ svn update`

要了解更多的 SVN 子命令，您可以参考手册。例如要了解 co (checkout) 命令，请执行：
`$ svn co --help`
`$ svn --help commit`
`☎ svn help cocheckout (co)`

一个实例：
	☎ killall svnserve; svnserve -d -r /home/svn/
	/home/svn/lj12-source/conf ☎ dog *authz:[groups]authz:lj12 = veexpauthz:[lj12-source:/] <- authzveexp ="rwauthz:@lj12"   rwauthz ="passwd:[users]"  -passwdveexp ="iceppasswd:test"   test svnserveconfgeneralsvnserveconfanon-access ="nonesvnserve.conf:auth-access"   writesvnserveconfpassword-db ="passwdsvnserve.conf:authz-db"   authz -authztestpre>
	☎ svn co svn://localhost/lj12-source --username veexp认证领域:  a712643f-661e-0410-8ad4-f0554cd88977用户名: veexp “veexp”的密码:A lj12-source/tim.h A lj12-source/en.c......

认证失败的密码缓冲记录位置，明文密码。到1.6版本，可能使用keyring管理。如果调试密码，直接删除如下文件就可。
`~/.subversion/auth/svn.simple/: eea34a6f7baa67a3639cacd6a428dba4`

###通过具被SSH隧道保护的自带协议访问(svn+ssh://) 
配置和服务器进程于上节所述相同。我们假设您已经运行了“svnserve”命令。
我们还假设您运行了 ssh 服务并允许接入。要验证这一点，请尝试使用 ssh 登录计算机。如果您可以登录，那么大功告成，如果不能，请在执行下面的步骤前解决它。
svn+ssh:// 协议使用 SSH 加密来访问 SVN 文件仓库。如您所知，数据传输是加密的。要访问这样的文件仓库，请输入：

	$ svn co svn+ssh://hostname/home/svn/myproject myproject --username user_name

注意：在这种方式下，您必须使用完整的路径(/home/svn/myproject)来访问 SVN 文件仓库
基于服务器的配置，它会要求输入密码。您必须输入您用于登录 ssh 的密码，一旦通过验证，就会签出文件仓库中的代码。
您还应该参考 SVN book 以了解关于 svn+ssh:// 协议的详细信息。



++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
配置svnserve实现svn://协议访问版本库

#内置的验证和授权
当客户端连接到一个svnserve进程时，下面的流程就会触发：
1)、客户选择一个指定的Repository；
2)、服务处理Repository的配置文件 conf/svnserve.conf文件，并且开始执行在其中定义的所有验证和授权策略；
3)、依赖与情形和授权策略：
(a)客户端也许允许匿名访问而不需要验证，或者
(b)客户但也许需要在任何时候被要求验证，或者
(c)假如处于"隧道模式"中，客户端将声明自己已经可以被外部验证。
很显然，如上所说，用户文件是一个名为svnserve.conf的，放在conf目录下的文件。
现在我们来看看如何配置这个文件：

1.创建仓库 svnadmin create /home/svnrepo
/root/svnrepo为所创建仓库的路径，理论上可以是任何目录

#访问权限设置
2.修改配置文件/home/svnrepo/conf/svnserve.conf
#去掉#[general]前面的#号
[general]
#匿名访问的权限，可以是read,write,none,默认为read
anon-access = none
#认证用户的权限，可以是read,write,none,默认为write
auth-access = write
#密码数据库的路径，去掉前面的#
password-db = passwd

注意：所有的行都必须顶格，否则报错。

3.修改配置文件passwd。
[users]
sxy = sxy
svnuser = password
jesszjessz = jessz 

注意：
a. 一定要去掉[users]前面的#,否则svn只能以匿名用户登录，客户端不会出现登录窗口，除非你的anon不为none,否则将返回一个错误。
b. 这里的密码都是没有加密的，我按照一些教程所说的用htpasswd生成的密码无法使用。

4.配置SVN xinetd启动方式：
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

5.停止SVN服务器：killall svnserve

6.启动SVN服务器
a).对于单个代码仓库: svnserve -d -r /home/svn --listen-host 192.168.1.16
其中-d表示在后台运行，-r指定服务器的根目录，这样访问服务器时就可以直接用svn://服务器ip来访问了。如果服务器有多ip的话--listen-host来指定监听的ip地址.
我们可以在svn客户端中通过svn://192.168.1.16来访问svn服务器
b).对于多个代码仓库,我们在启动时也可以用-r选项来指定服务器根目录,但访问时需要写上每个仓库相对于svn根目录的相对路径.
比 如,我们有两个代码仓库/home/repo1 和/home/repo2,我们用svnserve -d -r /home--listen-host 192.168.1.16来启动,那么在客户端访问时可以用svn://192.168.1.16/repo1和svn://192.168.1.16/repo2来分别访问两个项目

(1).检查是否正常启动
$ netstat -ntlp
可以看到有一个端口为3690的地址，表示启动成功
(2).局域网访问，checkout出来SVN库的文件
svn checkout svn://SvnIp地址/mypro

7.开放服务器端口
svn默认端口是3690，你需要在防火墙上开放这个端口。
/sbin/iptables -A INPUT -i eth0 -p tcp --dport 3690 -j ACCEPT
/sbin/service iptables save
你也可以通过svnserve的--listen-port选项来指定一个已经开放的其他端口,不过这样的话客户端使用也必须家上端口,如svn://192.168.1.200:9999/.

8.使用svn客户端导入项目

推荐使用客户端 http://tortoisesvn.tigris.org/
eclipse插件 http://subclipse.tigris.org/



++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
在Ubuntu下使用Apache配置Subversion实现http://协议访问版本库
1.安装必要软件
$ sudo apt-get install subversionlibapache2-svnapache2
2.修改apache配置文件/etc/apache2/mods-available/dav_svn.conf
mypro<
DAV svn
SVNPath /home/xiaozhe/svn/mypro
AuthType Basic
AuthName "myproject subversion repository"
AuthUserFile /etc/subversion/passwd
#
Require valid-user
#

如果需要用户每次登录时都进行用户密码验证，请将与两行注释掉。
当您添加了上面的内容，您必须重新起动 Apache 2 Web 服务器，请输入下面的命令：
$ sudo /etc/init.d/apache2 restart

3.创建 /etc/subversion/passwd 文件，该文件包含了用户授权的详细信息
$ sudo htpasswd -c /etc/subversion/passwd user_name
它会提示您输入密码，当您输入了密码，该用户就建立了。“-c”选项表示创建新的/etc/subversion/passwd文件，所以user_name所指的用户将是文件中唯一的用户。如果要添加其他用户，则去掉“-c”选项即可：$ sudo htpasswd /etc/subversion/passwd other_user_name
4.您可以通过下面的命令来访问文件仓库：
$ svn co http://hostname/svn/myproject myproject --username user_name
或者通过浏览器：http://hostname/svn/myproject


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
svn ignore:

若想创建了一个文件夹，并且把它加入版本控制，但忽略文件夹中的所有文件的内容：
$ svn mkdir spool
$ svn propset svn:ignore '*' spool
$ svn ci -m 'Adding "spool" and ignoring its contents.'

若想创建一个文件夹，但不加入版本控制，即忽略这个文件夹：
$ mkdir spool
$ svn propset svn:ignore 'spool' .
$ svn ci -m 'Ignoring a directory called "spool".'


若已经创建了文件夹，并加入了版本控制，现在想忽略这个文件夹，但要保持文件夹的内容：
$ svn export spool spool-tmp
$ svn rm spool
$ svn ci -m 'Removing inadvertently added directory "spool".'
$ mv spool-tmp spool
$ svn propset svn:ignore 'spool' .
$ svn ci -m 'Ignoring a directory called "spool".'


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
VN（Subversion）是一个自由、开源的项目源代码版本控制工具。目前，绝大多数开源软件和企业代码管理，都使用SVN作为代码版本管理软件。

Subversion将文件存放在中心版本库里，这个版本库很像一个普通的文件服务器。不同的是，它可以记录每一次文件和目录的修改情况，这样就可以在需要的回滚时，将数据恢复到以前的版本，并可以查看数据的更改细节。

SVN 官方网址：Apache Subversion

SVN 服务器配置：安装SVN服务器


一、 SVN常用命令

1、将文件checkout到本地目录
svn checkout path（path是服务器上的目录）
简写：svn co

2、往版本库中添加新的文件
svn add file

3、将改动的文件提交到版本库
svn commit -m “LogMessage” [-N] [--no-unlock] PATH(如果选择了保持锁，就使用–no-unlock开关)
简写：svn ci

4、加锁/解锁
svn lock -m “LockMessage” [--force] PATH
svn unlock PATH

5、更新到某个版本
svn update -r m path
简写：svn up

6、查看文件或者目录状态
1）svn status path（目录下的文件和子目录的状态，正常状态不显示）
2）svn status -v path(显示文件和子目录状态)
简写：svn st

7、删除文件
svn delete path -m “delete test fle”
简写：svn (del, remove, rm)

8、查看日志
svn log path

9、查看文件详细信息
svn info path

10、比较差异
svn diff path(将修改的文件与基础版本比较)
svn diff -r m:n path(对版本m和版本n比较差异)
简写：svn di

11、将两个版本之间的差异合并到当前文件
svn merge -r m:n path

12、SVN 帮助
svn help
svn help ci

 


 二、 SVN不常用命令
 13、版本库下的文件和目录列表
   svn list path    显示path目录下的所有属于版本库的文件和目录简写：svn ls

   14、创建纳入版本控制下的新目录
   svn mkdir: 创建纳入版本控制下的新目录。
   用法: 
   1、mkdir PATH...
   每一个以工作副本 PATH 指定的目录，都会创建在本地端，并且加入新增调度，以待下一次的提交。
   2、mkdir URL... 创建版本控制的目录。 
   每个以URL指定的目录，都会透过立即提交于仓库中创建。在这两个情况下，所有的中间目录都必须事先存在。

   15、恢复本地修改
   svn revert: 恢复原始未改变的工作副本文件 (恢复大部份的本地修改)。
   用法: revert PATH... 注意: 本子命令不会存取网络，并且会解除冲突的状况。但是它不会恢复被删除的目录

   16、代码库URL变更
   svn switch (sw): 更新工作副本至不同的URL。
   用法: 
   1、switch URL [PATH]        
   更新你的工作副本，映射到一个新的URL，其行为跟“svn update”很像，也会将      服务器上文件与本地文件合并。这是将工作副本对应到同一仓库中某个分支或者标记的方法。 
   2、switch --relocate FROM TO [PATH...]   
   改写工作副本的URL元数据，以反映单纯的URL上的改变。当仓库的根URL变动     (比如方案名或是主机名称变动)，但是工作副本仍旧对映到同一仓库的同一目录时使用     这个命令更新工作副本与仓库的对应关系。

   17、解决冲突
   svn resolved: 移除工作副本的目录或文件的“冲突”状态。
   用法: resolved PATH... 注意: 本子命令不会依语法来解决冲突或是移除冲突标记；它只是移除冲突的相关文件，然后让 PATH 可以再次提交。

   18、输出指定文件或URL的内容。
   svn cat 目标[@版本]...如果指定了版本，将从指定的版本开始查找。 svn cat -r PREV filename > filename (PREV 是上一版本,也可以写具体版本号,这样输出结果是可以提交的）
    


	三、 SVN其它命令

	虽然不像本章先前讨论过的那些命令那么常用，但是有时你也需要这些命令。 

	svn cleanup
	当Subversion修改你的工作副本时（或者任何在.svn中的信息），它尝试尽可能做到安全。在改变一个工作副本前，Subversion把它的意 图写到一个日志文件中。接下来它执行日志文件中的命令来应用要求的修改。最后，Subversion删除日志文件。从架构上来说，这与一个日志文件系统 （journaled filesystem）类似。如果一个 Subversion操作被打断（例如，进程被杀掉了，或机器当掉了）了，日志文件仍在硬盘上。重新执行日志文件，Subversion可以完成先前开始 的操作，这样你的工作副本能回到一个可靠的状态。 

	以下是svn cleanup所做的：它搜索你的工作副本并执行所有遗留的日志，在这过程中删除锁。如果Subversion曾告诉你你的工作副本的一部分被“锁定”了，那么你应该执行这个命令。另外， svn status会在锁定的项前显示L。 

	$ svn status
	L    somedir
	M   somedir/foo.c 

	$ svn cleanup
	$ svn status
	M      somedir/foo.c

	svn import
	使用svn import是把未版本化的文件树复制到资料库的快速办法，它需要创建一个临时目录。 

	$ svnadmin create /usr/local/svn/newrepos
	$ svn import mytree file:///usr/local/svn/newrepos/some/project
	Adding         mytree/foo.c
	Adding         mytree/bar.c
	Adding         mytree/subdir
	Adding         mytree/subdir/quux.h

	Committed revision 1.

	上面的例子把在some/project目录下mytree目录的内容复制到资料库中。 

	$ svn list file:///usr/local/svn/newrepos/some/project
	bar.c
	foo.c
	subdir/

	注意在导入完成后，原来的树没有被转化成一个工作副本。为了开始工作，你仍然需要svn checkout这个树的一个新的工作副本。


	SVN实例

	删除目录下所有的 .svn 隐藏子目录

	find . -name ".svn" -print0 | xargs -0 rm -rf


	tags打分支

	svn  cp  trunk/    tags/platform_2011.11.11    （或 svn  cp  http://192.168.1.100/platform/trunk/    http://192.168.1.100/platform/tags/platform_2011.11.11）

	svn  ci  -m  "svn  cp  trunk/    tags/platform_2011.11.11"         // 提交，并给出提交记录（-m  "svn  cp  trunk/    tags/platform_2011.11.11"）


	svn 改名

	svn  mv  platform_2011.11.11   platform_20111111

	svn  ci  -m  "svn  mv  platform_2011.11.11   platform_20111111"        // 提交


	svn directory is missing

	1） svn up missingDirName
	2） svn del missingDirName
	3） svn ci


	svn chech version

	svn  co  http://192.168.1.100/platform/branch  -r  12  platform_branch_v12


	svn log

	svn  log  http://192.168.1.100/platform/branch  -l10              // svn  文字注释log

	svn  log  http://192.168.1.100/platform/branch  -l10  -v          // svn 文字注释log + 文件更新log（增，删，改）


	svn diff -r  v_1 : v_2 svn_path

	svn diff -r 200:201 test.php


	查看svn版本

	svnserve --version

	ubuntu 安装svn 1.7、1.8

	当前 ubuntu 12.04 中的 svn 版本为 1.6，这个版本会在每个子目录新建一个.svn 的目录保存版本文件，很不爽。找到一个第三方编译的 ubuntu 源：

	1） 打开source.list源：

	sudo vi /etc/apt/sources.list   

	2） 添加源

	deb http://ppa.launchpad.net/dominik-stadler/subversion-1.7/ubuntu precise main

	deb-src http://ppa.launchpad.net/dominik-stadler/subversion-1.7/ubuntu precise main


	3） 执行安装命令

	sudo apt-get install subversion


++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
名词说明：

WC：Working Copy 你的工作区

Versioned：受控的；受版本控制的

 

SVN是什么？

 

    SVN是开源的版本控制系统。
    比CVS更多的特性。一个更好的CVS？因此SVN具有大部分CVS拥有的特性。
    不仅仅是文件受控，目录也加入版本控制。
    复制，删除，重命名这些操作都是受控的。
    特殊作用的元数据（属性）。
    提交事务原子性。提交完成之前任何一个部分都不会正真生效。版本号基于提交，而不是基于文件。提交时的log message也是依附于提交的那个版本。
    创建分支和标记非常简单。简单的通过copy命令就可以创建分支和标记。
    合并跟踪。在合并时协助你处理所有的更改点。
    文件锁定。svn支持文件锁定修改策略。
    Unix的link可以受控了。前提是WC必须在Unix下。
    可选的Apache network server，基于WEBDAV/DeltaV 协议。熟悉Apache的管理员会很喜欢这一点。
    内置的server选择（svnserve）。如果不想用Apache，可以试试Svn自己的server：svnserve。同样也能提供授权和验证，ssh通道等功能。
    方便解析的输出。svn的输出尽量做到方便阅读和方便机器解析。
    冲突解决交互性良好。svn命令行客户端提供多种不同的方式解决冲突。
    svn提供一个实用工具，svnsync来实现从主库到只读附属库的同步。
    持续写入代理功能让只读的附属库专门处理所有的读请求。所有的写请求交给主库处理。这个功能只在使用Apache WebDAV server的时候才有效。
    基于本地化的客户机服务器体系，分层的库，明晰的API方便扩展。
    高效处理二进制文件。
    性能消耗与更改点的数量成正比。
    svn的api可以和多种语言集成。Python，Perl,Java,Ruby（svn本身是用C写的）
    ChangeLists功能。

Svn的安装分客户端和服务端。

你可以在如下地址找到下载：http://subversion.tigris.org/

这篇文章主要介绍的是svn客户端的命令，你至少需要安装客户端。默认就是以SVN做版本控制的。如果你不想在自己机器上安装服务版，google code是个练习svn命令的好地方。

http://code.google.com上申请托管项目很简单，但是现在不支持svn lock。目前最大支持1G空间。

 

以下是svn客户端常用命令一览：

 

svn add [path]

别名：无

描述：添加文件或目录到你的wc，打上新增标记。这些文件会在下一次你提交wc的时候提交到svn服务器。

在提交前，你也可以用svn revert撤销新增的文件。

访问库：否

eg: svn add file.cpp

 

svn blame Target[@REV]

别名：praise,annotate,ann

描述：显示某个已受控文件的每一行的最后修改版本和作者

访问库：是

eg: svn blame file.cpp

eg: svn blame --xml file.cpp  ##加上xml参数可以以xml格式显示每一行的属性。

 

svn cat TARGET[@REV]

别名：无

描述：输出指定目标的内容，这里的目标一般是文件。

访问库：是

eg:svn cat file.cpp

eg:svn cat file.cpp -r 2 ##显示版本号为二的file.cpp内容。

eg:svn cat file.cpp --revision HEAD ##显示最新版本的file.cpp内容。

 

svn changelist CLNAME TARGET...

svn changelist --remove TARGET

别名：cl

描述：可以将wc中的文件从逻辑上分组.

访问库：否

eg:svn cl clName file.cpp file2.cpp file3.cpp  ##将file.cpp等三个文件加入名叫clName的changelist 

eg:svn commit --changelist clName -m "ci"  ##将clName下的所有文件提交

 

svn checkout URL[@REV]... [PATH]

别名：co

描述：检出

访问库：否

eg:svn checkout file:///var/svn/repos/test  file:///var/svn/repos/quiz working-copies

eg:svn checkout -r 2 file:///var/svn/repos/test mine  ##check out 版本号为2的项目

 

svn cleanup [PATH...]

别名：无

描述：递归的清理WC中过期的锁和未完成的操作。

访问库：否

eg：svn cleanup

 

svn commit [PATH...]

别名：ci

描述：把你WC的更改提交到仓库

访问库：是

eg：svn commit -m "added howto section." ##默认情况下提交必须提供log message 

 

svn copy SRC[@REV]... DST

别名：cp

描述:copy操作可以从WC到WC；WC到URL；URL到WC；URL到URL。现在SVN只支持同一个仓库内文件的拷贝，不允许跨仓库操作。

访问库：是

eg：svn copy -r 11 file:///var/svn/repos/test/trunk \

           file:///var/svn/repos/test/tags/0.6.32-prerelease \

           -m "Forgot to tag at rev 11"

##copy命令是创建分支和标记的常用方式。copy到url的操作隐含了提交动作，所以需要提供log messages。

 

svn delete PATH...

别名：del，remove，rm

描述：删除

访问库：如果PATH是库地址时会，删除WC内的文件不会。

eg：svn del localfile.cpp    ##删除WC里的文件，在下一次提交WC的时候才会真正在仓库里将对应文件删除。

eg: svn del file:///var/svn/repos/test/yourfile  ##删除仓库里的文件

 

svn diff

别名：di

描述：用来比较并显示修改点。

访问库：

eg：svn diff   ##最常用的方式，用来显示WC基于最近一次更新以后的所有的本地修改点。

eg：svn diff -r 301 bin ## 比较WC和版本301中的bin目录的修改点

eg：svn diff -r 3000:3500 file:///var/svn/repos/myProject/trunk   ##比较库里主干3000版和3500版的差异。

eg：svn diff --summarize --xml http://svn.red-bean.com/repos/test@r2 http://svn.red-bean.com/repos/test  ##--summarize --xml 参数将差异情况以xml文档的方式显示出来。

 

svn export [-r REV] URL[@PEGREV] [PATH]

svn export [-r REV] PATH1[@PEGREV] [PATH2]

别名：无

描述：导出一个干净的目录树，不包含所有的受控信息。可以选择从URL或WC中导出。

访问库：如果访问的是URL则会。

eg：svn export file:///var/svn/repos my-export   ##导出到my-export目录。

 

svn help — Help!

别名：?,h

描述：不用解释了

访问库：否。

 

svn import [PATH] URL

别名：无

描述：导入本地一个目录到库中。但是导入后，本地的目录并不会处于受控状态。

访问库：是。

eg：svn import -m "New import" myproj http://svn.myProject.com/repos/trunk/misc

 

svn info [TARGET[@REV]...]

别名：无

描述：显示指定WC和URL信息。

访问库：仅当访问的是库路径时。

eg：svn info --xml http://svn.myProject.com/repos/test  ##将信息以xml格式显示。

 

svn list [TARGET[@REV]...]

别名：ls

描述：显示目标下的文件和目录列表。

访问库：如果访问的是库地址就会。

eg：svn list --verbose file:///var/svn/repos   ##--verbose参数表示显示详细信息。

 

svn lock TARGET...

别名：无

描述：对目标获得修改锁。如果目标已被其他用户锁定，则会抛出警告信息。用--force参数强制从其他用户那里获得锁。

访问库：是

eg：svn lock --force tree.jpg

 

svn log [PATH]

svn log URL[@REV] [PATH...]

别名：无

描述：从库中显示log消息。log消息代码 A ：added  D：deleted  M：modified  R：replaced

访问库：是

eg：svn log -v http://svn.myProject.com/repos/test/ foo.c bar.c   ##详细显示指定URL的库中foo.c和bar.c所有版本的log信息。

eg：svn log -r 14:15    ##显示当前WC的14和15版本log信息。

eg：##如果版本号不连续，只能采用如下方式。

$ svn log -r 14 > mylog

$ svn log -r 19 >> mylog

$ svn log -r 27 >> mylog

 

svn merge sourceURL1[@N] sourceURL2[@M] [WCPATH]

svn merge sourceWCPATH1@N sourceWCPATH2@M [WCPATH]

svn merge [[-c M]... | [-r N:M]...] [SOURCE[@REV] [WCPATH]]

别名：无

描述：合并两个受控源的不同之处，存放到一个WC里。

访问库：只有当访问库地址时。

eg：svn merge --reintegrate http://svn.example.com/repos/calc/branches/my-calc-branch  ##合并分支上的改变项到WC，往往用于分支合并到主干。

eg：svn merge -r 156:157 http://svn.example.com/repos/calc/branches/my-calc-branch   ##将制定URL版本156到157的所有更新合并到WC。

 

svn mkdir PATH...

svn mkdir URL...

别名：无

描述：在WC或库路径创建目录

访问库：只有当访问库地址时。

eg：svn mkdir newdir

 

svn move SRC... DST

别名：mv, rename, ren

描述：等同于svn copy命令跟个svn delete命令。WC到URL的重命名是不被允许的。

访问库：只有当访问库地址时。

eg：svn move foo.c bar.c  ##将foo.c改名成bar.c。

 

svn propdel PROPNAME [PATH...]

svn propdel PROPNAME --revprop -r REV [TARGET]

别名：pdel, pd

描述：从受控文件，目录等删除属性。第二种是删除某个指定版本上的附加属性。

访问库：只有当访问库地址时。

eg：svn propdel svn:mime-type someFile    ##从someFile上移除svn:mime-type这个属性。

 

svn propedit PROPNAME TARGET...

svn propedit PROPNAME --revprop -r REV [TARGET]

别名：pedit, pe

描述：编辑属性

访问库：只有当访问库地址时。

eg：svn propedit svn:keywords  file.c  ##修改file.c上的svn:keywords属性。

 

svn propget PROPNAME [TARGET[@REV]...]

svn propget PROPNAME --revprop -r REV [URL]

别名：pget,pg

描述：从文件，目录或版本取得指定属性的值。

访问库：只有当访问库地址时。

eg：svn propget svn:keywords file.c   ##从file.c中取得svn:keywords属性的值

 

svn proplist [TARGET[@REV]...]

svn proplist --revprop -r REV [TARGET]

别名：plist, pl

描述：列出文件、目录或版本上的所有附加属性

访问库：只有当访问库地址时。

eg：svn proplist --verbose file.c

 

svn propset PROPNAME [PROPVAL | -F VALFILE] PATH...

svn propset PROPNAME --revprop -r REV [PROPVAL | -F VALFILE] [TARGET]

别名：pset,ps

描述：给文件、目录或版本附加属性并赋值

访问库：只有当访问库地址时。

eg：svn propset svn:mime-type image/jpeg file.jpg   ##给file.jpg附加属性svn:mime-type 其值为image/jpeg

eg:svn propset --revprop -r 25 svn:log "Journaled about trip to New York."

##给版本25补上log message

eg:svn propset svn:ignore '.classpath' . 

##在本地忽略掉.classpath文件

 

svn resolve PATH...

别名：无

描述：将冲突的文件标记为已解决，并且删掉冲突产生的临时文件。注意这个命令并不是能把冲突解决，解决冲突还是得靠人工。

访问库：否

eg：svn resolve --accept mine-full foo.c   ##1.5版本后，加上--accept参数，尝试自动处理冲突。

 

svn resolved PATH...

别名：无

描述：已过时，被resolve --accept取代。去除冲突的状态和冲突临时文件。

访问库：否

 

svn revert PATH...

别名：无

描述：还原WC中所有的本地更改。

访问库：否

eg：svn revert --depth=infinity .   ##将整个目录所有文件还原

 

svn status [PATH...]

别名：stat, st

描述：输出WC中文件和目录的状态。如果WC提交，这些状态就会同步到库里。

一般状态有         ' '  没有修改

'A'  新增

'D'  删除

'M'  修改

'R'  替代

'C'  冲突

'I'  忽略

'?'  未受控

'!'  丢失，一般是将受控文件直接删除导致

访问库：加上--show-updates参数时会

eg：svn status wc

 

svn switch URL[@PEGREV] [PATH]

svn switch --relocate FROM TO [PATH...]

别名：sw

描述：将WC转向一个其他的库地址同步

访问库：是

eg：svn sw http://svn.myProject.com/repos/trunk/vendors .  ##将当前WC切换到另一个URL

 

svn unlock TARGET...

别名：无

描述：解锁

访问库：是

eg：svn unlock somefile

 

svn update [PATH...]

别名：up

描述：更新WC，更新反馈有如下几种分类。

        A  新增

B  锁破坏

D  删除

U  更新

C  冲突

G  合并

E  存在的

访问库：是

eg：svn up -r22   ##更新到一个指定版本


@echo off
if "%1"=="" (
 goto error
 ) else (
  goto action %1
  )

  :error
  echo.
  echo 必须输入要操作的文件夹路径参数，或拖动文件夹到此命令文件上。
  echo.
  pause
  goto end

  :action %1
  echo --------------------------------------------------------------------------
  echo 本次操作将删除 [%1] 文件夹下所有的svn标记，请慎重操作！
  echo     Y 清理文件夹
  echo     N 退出
  echo ---------------------------------------------------------------------------
  choice /c YN /m 请选择菜单(按ctrl+c或N退出)：

  if %errorlevel% equ 2 goto end
  echo 正在清理文件夹：%1
  echo 请稍候...
  for /r %1 %%a in (.) do @if exist "%%a\.svn" rd /s /q "%%a\.svn"
  echo 清理完毕!
  echo 按任意键退出...
  pause>echo.

  :end
  exit

  @for /r . %%a in (.) do @if exist "%%a\.svn" rd /s /q "%%a\.svn"

  
  
  
  
  
##git 中的常量

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

##git 的基本命令

___

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

git add 命令 | 含义
:-------------- | :------------
git add file_name       |加单个文件
git add .          |加当前目录的所有文件
git add -i |进入交互式add
git add -p |直接进入补丁模式，可以暂存修改的一部分。

<span style="white-space:nowrap">git commit 命令</span> | 含义
:-------------- | :------------
<span style="white-space:nowrap">git commit -a</span> | 第一步：自动地add所有改动的代码，使得所有的开发代码都列于index file中；第二步：自动地删除那些在index file中但不在工作树中的文件；第三步：执行commit命令来提交。
  
git push 命令 | 含义
:-------------- | :------------
git push origin test:test2 |提交本地test分支作为远程test2分支
git push origin test |提交本地test分支作为远程test分支
git push origin :test |删除远程test分支
git push origin :refs/tags/t4 |删除远程tag标签t4

git pull 命令 | 含义
:-------------- | :------------
git pull origin test:test2 |取回远程的test分支作为本地的test2分支

git checkout 命令 | 含义
:-------------- | :------------
git checkout test |如果本地无test分支，先需要从远程pull回test分支

git branch 命令 | 含义
:-------------- | :------------
git branch b4 t4 |以tag t4建立新的分支b4

git merge 命令 | 含义
:-------------- | :------------
git merge AAA      |将分支AAA与当前分枝合并

git diff&nbsp;命令 | 含义
:-------------- | :------------
git diff&nbsp; |查看working tree与index file的差别的（这个命令只在git add之前使用有效。如果已经add了，那么此命令输出为空）。
<span style="white-space:nowrap">git diff --cached</span> |查看index file与commit的差别的（这个命令在git add之后在git commit之前有效。）。
git&nbsp;diff&nbsp;HEAD |查看working tree和commit的差别的。（你一定没有忘记，HEAD代表的是最近的一次commit的信息）

git reset 命令 | 含义
:-------------- | :------------
git reset --soft |只撤销commit，保留working tree和index file。
<span style="white-space:nowrap">git reset --mixed</span> |撤销commit和index file，保留working tree
git reset --hard |撤销commit、index file和working tree，即撤销销毁最近一次的commit
git reset |和git reset --mixed完全一样
git reset -- |用于删除登记在index file里的某个文件。例如：git reset -- roc.c

git revert 命令 | 含义 
:-------------- | :------------
git revert |用于回滚（撤销）一些commit。对于一个或者多个已经存在的commit，去除由这些commit引入的改变，并且用一个新的commit来记录这个回滚操作。这个命令要求working tree必须是干净的。 
git revert HEAD~3 |丢弃最近的三个commit，把状态恢复到最近的第四个commit，并且提交一个新的commit来记录这次改变。 
<span style="white-space:nowrap">git revert -n master~5..master~2</span> |丢弃从最近的第五个commit（包含）到第二个（不包含）,但是不自动生成commit，这个revert仅仅修改working tree和index。 

 其它命令 | 含义
:-------------- | :------------
git rebase |
git submodule | （1、2）



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
[Git 初學筆記 - 指令操作教學](http://blog.longwin.com.tw/2009/05/git-learn-initial-command-2009/)    
[Git Magic](http://www-cs-students.stanford.edu/~blynn/gitmagic/intl/zh_cn/)      
[GetGitHub](http://www.worldhello.net/gotgithub/index.html)   
[超级有用的git reset --hard和git revert命令](http://blog.sina.com.cn/s/blog_68af3f090100rp5r.html)   
[Git-rebase 小筆記](http://blog.yorkxin.org/2011/07/29/git-rebase)   
[版本控制系統 Git 精要](http://ihower.tw/git/)      
[Pro Git](http://git-scm.com/book/zh)     
