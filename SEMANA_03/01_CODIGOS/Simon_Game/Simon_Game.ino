int ProxFase = 0; //armazena o próximo número a ser adicionado a sequência
int Fases[20]; //guarda a sequência a ser lembrada pelo jogador, definindo o número máximo de fases como 20

int Jogador = 0; //armazena o input do jogador

int Nivel = 0; //nível atual do jogo
int Contador= 0; //verifica o input do jogador em relação à sequência dada pelo jogo
bool Sort = true; //define se a sequência deve ser mostrada novamente ou não (false = jogador errou a última rodada)

void reiniciar() //reseta a sequência
{
  //LEDs piscam --> jogo reiniciou
  digitalWrite(33, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);
  delay(1000);
  digitalWrite(33, LOW);
  digitalWrite(25, LOW);
  digitalWrite(26, LOW);
  digitalWrite(27, LOW);
  delay(1000);
  Nivel = 0;//zera os níveis
  Sort = true;//define Sort como verdadeiro
  Contador = 0; //reseta o contador de verificação.

}

void Perdeu() //indica quando o jogador comete um erro
{
  for(int i=0; i<=3; i++)//LED é aceso e apagado 4x
  {
    digitalWrite(33, HIGH);
    digitalWrite(26, HIGH);
    delay(100);
    
    digitalWrite(33, LOW);
    digitalWrite(26, LOW);
    delay(100);

    digitalWrite(25, HIGH);
    digitalWrite(27, HIGH);
    delay(100);

    digitalWrite(25, LOW);
    digitalWrite(27, LOW);
    delay(100);
  }


 for(int i=0; i<=10; i++)
 {
  Fases[i] = 0;//zera a var de fases
 }

 reiniciar();//aciona a função reiniciar
}

void Jogo()//mostra a sequência atual --> acende os LEDs de acordo com os números armazenados na matriz Fases. Toda vez que o jogo for reiniciado essa sequência muda
{
  for(int i=0; i<=Nivel; i++)//percorre cada elemento da sequência atual do jogo, checando através do Switch cada opção --> 4 casos, pois tem 4 opções
  {
    switch(Fases[i])
    {
      case 1:
      digitalWrite(33, HIGH);
      delay(500);
      digitalWrite(33, LOW);
      delay(500);
      break;

      case 2:
      digitalWrite(25, HIGH);
      delay(500);
      digitalWrite(25, LOW);
      delay(500);
      break;

      case 3:
      digitalWrite(26, HIGH);
      delay(500);
      digitalWrite(26, LOW);
      delay(500);
      break;
      
      case 4:
      digitalWrite(27, HIGH);
      delay(500);
      digitalWrite(27, LOW);
      delay(500);
    }
  }
}

void Check(int pinGame)//checa se, o que o jogador escolheu, condiz com a sequência certa
{
  if(Jogador == Fases[Contador])//verifica se a escolha do jogador condiz com o que foi armazenado no contador
  {
    digitalWrite(pinGame, HIGH);
    delay(500);
    digitalWrite(pinGame, LOW);
    delay(500);

    if(Contador == Nivel)//verifica se o jogador acertou todos os elementos
    {
      Nivel++;//passa pra próx rodada
      Contador = 0;//contador zera --> acompanhar a nova sequência
      Sort = true;//Sort fica como verdadeiro para que a sequência seja mostrada novamente
    }
    else
    {
      Contador++;//adc 1 no contador
    }
  }
  else //se não condizer, a função Perdeu é acionada
  {
   Perdeu(); 
  }
    
}

void setup() //define pinos dos botões e LEDs:
{
  Serial.begin(9600);

  pinMode(16, INPUT_PULLUP);//vermelho
  pinMode(17, INPUT_PULLUP);//azul
  pinMode(5, INPUT_PULLUP); //verde
  pinMode(18, INPUT_PULLUP);//amarelo

  pinMode(19, INPUT_PULLUP);//reinicia

  pinMode(33, OUTPUT);// vermelho
  pinMode(25, OUTPUT);// azul
  pinMode(26, OUTPUT);// verde
  pinMode(27, OUTPUT);// amarelo


  
  randomSeed(analogRead(0));

  delay(3000);
}

void loop()
{
  if(Nivel != 21)//caso o nível seja diferente de 21, o jogo roda
  {
     if(Sort)//se Sort for true, vai continuar mostrando a sequência aleatória pro jogador
     {
       ProxFase = random(1, 5);//escolhe um LED aleatório e armazena em ProxFase
       Fases[Nivel] = ProxFase;//armazena o número gerado em Fases no índice Nivel, que representa a sequência atual --> número gerado em ProxFase é armazenado em Fases no nível atual do jogo
       Jogo();//exibe a sequência para o jogador
     }
     
     Sort = false;//Sort é definida como falsa --> jogador repite o que foi feito

     //checa se, o que o jogador acionou, condiz com a sequência correta:
     if(digitalRead(16) == 0)
     {
       Jogador = 1;
       Check(33);
     }
      else if(digitalRead(17) == 0)
     {
       Jogador = 2;
       Check(25);
     }
      else if(digitalRead(5) == 0)
     {
       Jogador = 3;
       Check(26);
     }
      else if(digitalRead(18) == 0)
     {
       Jogador = 4;
       Check(27);
     }
     else if(digitalRead(19) == 0)//se apertar esse botão, o jogo reinicia
     {
       reiniciar();
     } 
  }
  else //se errar, o jogo reinicia
  {
    reiniciar();
  }
}
