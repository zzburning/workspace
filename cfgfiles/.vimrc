" don't bother with vi compatibility
set nocompatible

" enable syntax highlighting
syntax enable

" configure Vundle(Vim bundles)
filetype on " without this vim emits a zero exit status, later, because of :ft off
filetype off
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" install Vundle bundles
if filereadable(expand("~/.vimrc.bundles"))
  source ~/.vimrc.bundles
endif

call vundle#end()

" ensure ftdetect et al work by including this after the Vundle stuff
filetype plugin indent on

let mapleader = ','

" ===plugin settings=========================================
"ack or ag{
  " Use The Silver Searcher https://github.com/ggreer/the_silver_searcher
  if executable('ag')
  let g:ackprg = 'ag --nogroup --column'

  " Use Ag over Grep
  set grepprg=ag\ --nogroup\ --nocolor

  " Use ag in CtrlP for listing files. Lightning fast and respects .gitignore
  let g:ctrlp_user_command = 'ag %s -l --nocolor -g ""'
  endif
  map <F2> "zyw:exe "Ack ".@z.""<CR>
  nmap <leader>a :Ack<space>
"}

"ctrlp{
  let g:ctrlp_match_window = 'order:ttb,max:20'
  nmap <leader>p :CtrlP<CR>
  nmap <leader>b :CtrlPBuffer<CR>
" nmap <leader>T :CtrlPClearCache<CR>:CtrlP<CR>
"

"tagbar{
  nmap <leader>t :TagbarToggle<cr>
"}


"taglist{
  let Tlist_Show_One_File = 1            "只显示当前文件的taglist，默认是显示多个
  let Tlist_Exit_OnlyWindow = 1          "如果taglist是最后一个窗口，则退出vim
  let Tlist_Use_Right_Window = 1         "在右侧窗口中显示taglist
  let Tlist_GainFocus_On_ToggleOpen = 1  "打开taglist时，光标保留在taglist窗口
  let Tlist_File_Fold_Auto_Close=1       "自动折叠
  nnoremap <leader>T :Tlist<CR>          "设置关闭和打开taglist窗口的快捷键
"}

"ctags{
  set tags=./.tags,.tags,./../.tags,./../../.tags
  nmap <silent> <leader>C :!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q -f .tags .<CR> 
"}

"cscope{
" if has("cscope")
"   set csprg=/usr/bin/cscope              "指定用来执行 cscope 的命令
"   set csto=1                             "先搜索tags标签文件，再搜索cscope数据库
"   set cst                                "使用|:cstag|(:cs find g)，而不是缺省的:tag
"   set nocsverb                           "不显示添加数据库是否成功
"   if filereadable("cscope.out")			" add any database in current directory
" 	cs add cscope.out                   "添加cscope数据库
"   endif
"   set csverb							 "显示添加成功与否
" endif
"   nmap s :cs find s =expand("")
"   nmap g :cs find g =expand("")
"   nmap c :cs find c =expand("")
"   nmap t :cs find t =expand("")
"   nmap e :cs find e =expand("")
"   nmap f :cs find f =expand("")
"   nmap i :cs find i ^=expand("")$
"   nmap d :cs find d =expand("")
"}

"authorinfo{
  let g:vimrc_author='zzburning'
  let g:vimrc_email='zzburning@gmail.com'
  let g:vimrc_homepage=''
  nmap <silent> <leader>A :AuthorInfoDetect<cr>
"   nmap <silent> <leader>C :call append(line("."),strftime("%b-%d-%Y")."  wangtao<wangtao@hisome.com>")<cr>
"}

" for ycm
" highlight Pmenu ctermfg=2 ctermbg=3 guifg=#005f87 guibg=#EEE8D5
" highlight PmenuSel ctermfg=2 ctermbg=3 guifg=#AFD700 guibg=#106900
let g:ycm_global_ycm_extra_conf = '~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py'
let g:ycm_collect_identifiers_from_tags_files = 1 " Let YCM read tags from Ctags file
let g:ycm_seed_identifiers_with_syntax = 1 " Completion for programming language's keyword
let g:ycm_complete_in_comments = 1 " Completion in comments
let g:ycm_complete_in_strings = 1 " Completion in string
let g:ycm_error_symbol = '>>'
let g:ycm_warning_symbol = '>*'
" let g:ycm_use_ultisnips_completer = 1 " Default 1, just ensure

nnoremap <leader>gl :YcmCompleter GoToDeclaration<CR>
nnoremap <leader>gf :YcmCompleter GoToDefinition<CR>
nnoremap <leader>gg :YcmCompleter GoToDefinitionElseDeclaration<CR>
nmap <F4> :YcmDiags<CR>

let g:NERDSpaceDelims=1
let g:gitgutter_enabled = 0

"doxygen toolkit{
"   let g:DoxygenToolkit_briefTag_pre="@synopsis  "
"   let g:DoxygenToolkit_paramTag_pre="@param "
"   let g:DoxygenToolkit_returnTag="@returns   "
"   let g:DoxygenToolkit_blockHeader="--------------------------------------------------------------------------"
"   let g:DoxygenToolkit_blockFooter="----------------------------------------------------------------------------"
"   let g:DoxygenToolkit_authorName="Drunkedcat"
"   let g:DoxygenToolkit_licenseTag="GPL 2.0"
" 
"   let g:DoxygenToolkit_authorName="wangtao <wangtao@hisome.com>"
"   let s:licenseTag = "Copyright(C)\<enter>"
"   let s:licenseTag = s:licenseTag . "For free\<enter>"
"   let s:licenseTag = s:licenseTag . "All right reserved\<enter>"
"   let g:DoxygenToolkit_licenseTag = s:licenseTag
"   let g:DoxygenToolkit_briefTag_funcName="yes"
"   let g:doxygen_enhanced_color=1
"}

"omni complete (C-x,C-o)
"   set completeopt+=longest  								"离开插入模式后自动关闭预览窗口 
"   autocmd InsertLeave * if pumvisible() == 0|pclose|endif   "回车即选中当前项 
"   inoremap <expr> <CR> pumvisible() ? "\<C-y>" : "\<CR>"  	"上下左右键的行为 
"   inoremap <expr> <Down> pumvisible() ? "\<C-n>" : "\<Down>" 
"   inoremap <expr> <Up> pumvisible() ? "\<C-p>" : "\<Up>" 
"   inoremap <expr> <PageDown> pumvisible() ? "\<PageDown>\<C-p>\<C-n>" : "\<PageDown>" 
"   inoremap <expr> <PageUp> pumvisible() ? "\<PageUp>\<C-p>\<C-n>" : "\<PageUp>"
"}

"powerline{
" set guifont=PowerlineSymbols\ for\ Powerline
" set nocompatible
" set t_Co=256
" let g:Powerline_symbols = 'fancy'
" }
"
nmap <leader>d :NERDTreeToggle<CR>
nmap <leader>f :NERDTreeFind<CR>
nmap <leader>g :GitGutterToggle<CR>
nmap <leader>c <Plug>Kwbd
"map <leader>l :Align


"===local setting=====================================================
" Fix Cursor in TMUX
if exists('$TMUX')
  let &t_SI = "\<Esc>Ptmux;\<Esc>\<Esc>]50;CursorShape=1\x7\<Esc>\\"
  let &t_EI = "\<Esc>Ptmux;\<Esc>\<Esc>]50;CursorShape=0\x7\<Esc>\\"
  set ttymouse=xterm2
else
  let &t_SI = "\<Esc>]50;CursorShape=1\x7"
  let &t_EI = "\<Esc>]50;CursorShape=0\x7"
endif

if has("vms")
  set nobackup                      " do not keep a backup file, use versions instead
else
  set backup                        " keep a backup file
  set backupdir=~/.backup
endif

if (&t_Co == 256 || has('gui_running')) " gui settings
  if ($TERM_PROGRAM == 'iTerm.app')
    colorscheme solarized
  else
    colorscheme desert
  endif
endif

if &diff
  colorscheme darkblue
endif

set encoding=utf-8
set fileencoding=utf-8
set fileencodings=utf-8,gbk
set fileformats=unix,dos
set number                          " show line numbers
set ruler                           " show the cursor position all the time
set cursorline                      " show highlight current line
set shiftwidth=2                    " normal mode indentation commands use 2 spaces
set tabstop=4                       " actual tabs occupy 4 characters
" set expandtab                       " expand tabs to spaces
" set softtabstop=4                   " insert mode: tab & backspace use 4 spaces
set clipboard=unnamed               " yank and paste with the system clipboard
set incsearch                       " search as you type
set hlsearch
set autoindent
set backspace=2                     " Fix broken backspace in some setups
set directory-=.                    " don't store swapfiles in the current directory
set laststatus=2                    " always show statusline
set scrolloff=3                     " show context above/below cursorline
" set ignorecase                      " case-insensitive search
" set autoread                        " reload files when changed on disk, i.e. via `git checkout`
" set backupcopy=yes                  " see :help crontab
" set smartcase                       " case-sensitive search if any caps
" set list                            " show trailing whitespace
" set listchars=tab:▸\ ,trail:▫
" set wildignore=log/**,node_modules/**,target/**,tmp/**,*.rbc
" set wildmenu                        " show a navigable menu for tab completion
" set wildmode=longest,list,full
" set history=50                      " keep 50 lines of command line history
" set showcmd                         " display incomplete commands
" set mouse=a                         " Enable basic mouse behavior such as resizing buffers.
" 

"===keyboard shortcuts=================================
nmap <leader><space> :call whitespace#strip_trailing()<CR>
map <silent> <leader>S :source ~/.vimrc<CR>:filetype detect<CR>:exe ":echo 'vimrc reloaded'"<CR>
inoremap jj <ESC>
inoremap jk <ESC>

map <C-h> <C-w>h
map <C-j> <C-w>j
map <C-k> <C-w>k
map <C-l> <C-w>l
imap <A-h> <Left>
imap <A-l> <Right>

imap <leader>s <ESC>:w<CR>
set pastetoggle=<F9>


