
opt="`head -1 conf-opt`"
systype="`cat systype`"


case "$opt:$systype" in
  auto:*:i386-*:*:*:*)
    opt=x86-sched
    ;;
esac


case "$opt" in
  x86-sched)
    cat "$1/x86-sched.$2"
    ;;
  x86-idea)
    cat "$1/x86-idea.$2"
    ;;
  *)
    cat "$1/basic.$2"
    ;;
esac
