apt-get install vim tmux zsh git tree ack-grep ctags cscope python-pip

pip install httpie cheat
chsh -s /bin/zsh
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
git clone https://github.com/zzburning/workspace.git
# copy cfgfile to user home dir

# get ycm & compile
# cd ~/.vim/bundle/YouCompleteMe
# ./install.py --clang-completer --system-libclang --system-boost
# 
# cmake -G "Unix Makefiles" -DUSE_SYSTEM_LIBCLANG=ON . ~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp
# cmake --build . --target ycm_support_libs --config Release




