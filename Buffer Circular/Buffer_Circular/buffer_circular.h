#define ORDEM_FILTRO 3              // Ordem do filtro
double buffer_circular[ORDEM_FILTRO];
int posicao = 0;                    // Posicao da amostra atual

//double h[1];
// FIR -> Passa Baixa
/*double h[] = {
-0.002577596560087,  -0.006674494920200,  -0.011421090886231,   0.000000000000000,   0.048292532506363,   0.131859448571622,   0.215265391213767,
0.250511620149531,   0.215265391213767,   0.131859448571622,   0.048292532506363,   0.000000000000000,  -0.011421090886231,  -0.006674494920200,
-0.002577596560087
};*/

// FIR -> Passa Alta
double h[] = {
-0.025831542473523466,
 0.080544030207199885,
 -0.14332236778200783,
 0.17149625736922922 ,
 -0.14332236778200783,
 0.080544030207199885,
 -0.025831542473523466
};

// IIR -> Passa Alta
double a[] = {
 1, 0
};

double b[] = {
  0.5, -0.5
};

void atualiza_buffer(double nova_amostra){
    // Adiciona uma nova amostra e retira a mais antiga
    if (posicao == 0){
        posicao = ORDEM_FILTRO - 1;
    }else{
        posicao --;
    }
    buffer_circular[posicao] = nova_amostra;
}

void inicializa_buffer(){
    // Inicializa como zero as posicoes do filtro
    for (int i = 0; i < ORDEM_FILTRO; i++)
    {
        buffer_circular[i] = 0;
    }
    posicao = 0;
}

double get_value(int indice){
    int i = (posicao - indice) % ORDEM_FILTRO;
    if (i < 0)
      i = -i + posicao;
    return buffer_circular[i];
}

double fir(double nova_amostra){
    double resultado = 0;
    atualiza_buffer(nova_amostra);
    for (int i = 0; i < ORDEM_FILTRO; i++)
    {
        resultado += h[i] * get_value(i);
    }
    return resultado;
}

double iir(double nova_amostra){
  double soma_b = 0, soma_a = 0, resultado;

  for (int i = 0; i < ORDEM_FILTRO; i ++)
    soma_a += -a[i+1] * get_value(i);
   for (int i = 0; i < ORDEM_FILTRO; i ++)
    soma_b += b[i+1] * get_value(i);
  
  atualiza_buffer(nova_amostra);
  resultado = b[0] * (nova_amostra + soma_a) + soma_b;
  return resultado;
}
