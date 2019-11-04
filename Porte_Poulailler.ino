int sensPorteBrocheA = 8;
int sensPorteBrocheB = 9;
int vitessePorte = 10;
int capteur = 0;
int basdePorte = 3;
int hautdePorte = 4;
int securite = 2;
// declaration des variables 
int ValeurCapteur = 0;
int Var = 0;
int X = 0;
int testHaut = 0;
int testBas = 0;
int testSecurite = 0;
void setup ()

{
  pinMode (sensPorteBrocheA,OUTPUT) ;
  pinMode (sensPorteBrocheB,OUTPUT) ;
  pinMode (vitessePorte,OUTPUT);
  pinMode (capteur,INPUT) ;
  pinMode (basdePorte,INPUT) ;
  pinMode (hautdePorte,INPUT) ;

Serial.begin (9600) ;
}
void loop () 
{
    analogWrite (vitessePorte,0) ;
    ValeurCapteur = analogRead (capteur) ;
// prend la valeur du capteur 
  Serial.println ( ValeurCapteur);
  Serial.println ("attend le jour"); 
    Var = 0 ; 
    delay ( 6000 );  

  while (ValeurCapteur<200) // "200" valeur luminosité du matin à étalonner 
   {
    delay (600000); 
    ValeurCapteur = analogRead (capteur);    
   }  
// il fait jour la porte va s'ouvrir   
   ouvreLaPorte ();
   analogWrite (vitessePorte,0);   
   Serial.println ("la porte est ouverte le matin attente de la modification de la lumière pendant 1H" ); 
   delay (600000) ; // 10min pour teste 
 Serial.println ("prise de la nouvelle valeur" ); 
   ValeurCapteur = analogRead (capteur) ; 
 Serial.println ( ValeurCapteur); 
// cette valeur permet d'attendre la nuit  
Var = 0 ;                       
 // remise a zero de la boucle while 
  //..............................................
  // nouveau teste de lumiere pour attente de la nuit
  //..............................................
  while (ValeurCapteur > 200)
  {
   delay (600000);//10min
 //  pose pour  la boucle lumière à étalonner " passage du temps de nuit et de jours
   ValeurCapteur = analogRead (capteur) ;
  Serial.println ("attente de la nuit" ); 
  Serial.println (ValeurCapteur );
  }
Serial.println ("il fait nuit le capteur est plus petit que 200" );
 Serial.println (ValeurCapteur );
fermeLaPorte ();
}
  //............................................. 
  
  
  
  
  
  
  
  
  void ouvreLaPorte () 
 { 
  Var = 0 ;
Serial.println ( "debut boucle ouverture"); 
  sensHaut ();

  
  while (Var<60)

  {
    delay (5000) ; //5 sec

    int testHaut = digitalRead(hautdePorte);
    if (testHaut == HIGH )
    {
     analogWrite (vitessePorte,0);   

 Serial.println ("boucle ouverture le moteur tourne a 0" ); 
    }
    else
    {    
     analogWrite (vitessePorte,255) ;

Serial.println ("boucle ouverture le moteur tourne a 255"); 
    }
Serial.println ( Var);  
    Var ++ ;
       
  }
   
  
 }
  
  
  
  
  
  void fermeLaPorte () 
 { 
  Var = 0 ;
 Serial.println ( "debut boucle fermeture"); 
  sensBas ();
  while (Var<60)
// une boucle while pour un temps d'ouverture et un teste de butee de porte haute avec le switch
  {
    delay (5000) ; 
// permet le test toute les secondes
    int testBas = digitalRead(basdePorte);
    if (testBas == HIGH)
    {  
 Serial.println ("boucle fermeture le moteur tourne a 0" ); 
    analogWrite (vitessePorte,0);  
    }
    else
    {    
 Serial.println ("boucle fermeture le moteur tourne a 255" ); 
    analogWrite (vitessePorte,255) ;
    }
Serial.println ( Var);  
    Var ++ ;
  }

 }
  void sensBas ()
  {
    digitalWrite (sensPorteBrocheA, LOW);
    digitalWrite (sensPorteBrocheB, HIGH);
  }
  void sensHaut ()
  {
    digitalWrite (sensPorteBrocheA, HIGH);
    digitalWrite (sensPorteBrocheB, LOW);
  }
