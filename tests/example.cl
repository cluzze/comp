fst = 0;
snd = 0;
iters = ?;
while (iters > 0) {
  tmp = fst;
  fst = snd;
  snd = snd + tmp;
  iters = iters - 1;
}
if (snd > 0) {
  
}
print snd