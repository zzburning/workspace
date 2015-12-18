apt-get install vim tmux zsh git tree ack-grep ctags cscope python-pip
pip install httpie cheat
chsh -s /bin/zsh

sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
git clone https://github.com/zzburning/workspace.git

# # --copy cfgfile/{.tmux.conf, .vimrc, .vimr.bundles, .zshrc, .gitconfig, .gitignore_global} to user home dir
# # --install vim plugins
# vim -c "PluginInstall"
# # --compile ycm 
# cd ~/.vim/bundle/YouCompleteMe
# ./install.py --clang-completer --system-libclang --system-boost
# # --or
# cmake -G "Unix Makefiles" -DUSE_SYSTEM_LIBCLANG=ON . ~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp
# cmake --build . --target ycm_support_libs --config Release
# # --update c.vim
# wget http://www.vim.org/scripts/download_script.php?src_id=21803
# unzip cvim.zip -d c.vim
# cp -rf c.vim/* .vim/bundle/c.vim/
# rm -r c.vim



