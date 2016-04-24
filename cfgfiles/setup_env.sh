# # --install basic tools
sudo apt-get install vim tmux zsh git tree ack-grep ctags cscope python-pip unzip
sudo pip install httpie cheat
chsh -s /bin/zsh
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

# # --get common config files{.tmux.conf, .vimrc, .vimr.bundles, .zshrc,... }
rm -rf workspace
git clone https://github.com/zzburning/workspace.git
cp -f ~/workspace/cfgfiles/.[^.]* ~/

# # --install vim plugins
rm -rf ~/.vim/bundle/Vundle.vim workspace
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
vim +PluginClean +qall
vim +PluginInstall +qall
# vim -c "PluginClean" -c "qall"
# vim -c "PluginInstall" -c "qall"

# # --compile ycm 
# cd ~/.vim/bundle/YouCompleteMe
# ./install.py --clang-completer --system-libclang --system-boost
# # --or
# cmake -G "Unix Makefiles" -DUSE_SYSTEM_LIBCLANG=ON . ~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp
# cmake --build . --target ycm_support_libs --config Release

# # --update c.vim
wget http://www.vim.org/scripts/download_script.php?src_id=21803 -O cvim.zip
unzip cvim.zip -d c.vim
cp -rf c.vim/* .vim/bundle/c.vim/
rm -r c.vim cvim.zip

# # --install quickopen
git clone https://github.com/natduca/quickopen.git
cd quickopen
git submodule update --init --recursive
cd ~
sudo mv quickopen /opt/quickopen



