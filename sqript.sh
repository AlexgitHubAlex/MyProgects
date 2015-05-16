#!/bin/bash
# version 1.0
git clone https://github.com/gmarik/Vundle.vim.git ~/.vim/bundle/Vundle.vim
cp ./.vimrc ~/.vimrc

#vim plagin
vim +PluginInstall +qall
