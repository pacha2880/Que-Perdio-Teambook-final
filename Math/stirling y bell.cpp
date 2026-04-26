// stir[n][k] # formas de partir set tam n en k conjuntos
// bell[n] # de formas de partir un conjunto
ll stir[tam][tam]; bell[tam];
void stirBell() {
  fore(i, 1, tam) { stir[i][1] = 1; fore(j, 2, 1010)
  stir[i][j] = (j * stir[i - 1][j] %MOD+stir[i-1][j-1])%MOD; }
  fore(i,1,tam)fore(j,1,i+1)bell[i]=(bell[i]+stir[i][j])%MOD; }