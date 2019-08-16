//AUTHOR NAME:  Rithanathith.S
//DOMAIN:  Embedded and Analog electronics-TASK1
//TASK- 1
//SUB DOMAIN : Embedded system
//FUNCTIONS:  pwm_set, pwm_stop, timer1_initialize, play_note
//GLOBAL VARIABLE: none

//clock frequency =16MHz

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>


//REPRESENTS FREQUENCY FOR EACH NOTE 
#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494
#define pause 80


//FUNCTION NAME : pwm_set
//LOGIC : setting prescalar inorder to start timer1
//EXAMPLE CALL: pwm_set()
//only once after the prescalar is set ,timer1 counter starts
//writing 1 to CS11 will set prescalar of 8

 void pwm_set()
 {
 TCCR1B|=1<<CS11;// PRESCALAR of 8 
 OCR1A=0; 
 }


 
//FUNCTION NAME : pwm_stop
//LOGIC : reset prescalar inorder to stop timer1
//EXAMPLE CALL: pwm_stop()
//only once after the prescalar is reset ,timer1 counter stops

 void pwm_stop()
 {
  TCCR1B&=~(1<<CS11);
 }

 
//FUNCTION NAME : timer1_initialize
//LOGIC : initialize timer1 in Fast PWM and non-inverting mode
//EXAMPLE CALL: timer1_initiaze()
//clear OC1A ON compare match &set OC1A at bottom -NON INVERTING MODE
//setting wave generation mode 1,2,3 to 1 will enable the fast pwm mode

void timer1_initialize()
{
   TCCR1A|=1<<COM1A1;
   TCCR1A|=1<<WGM11;
   TCCR1B|=1<<WGM12|1<<WGM13;
  
}

//FORMULA USED:_
//pwm frequency =clock_frequency/[prescalar*(top+1)] 
//pwm_topX=[16000000/prescalar*(pwm frequency)]-1

 //pwm_top0 set the top_value for note C4 USING formula
 //pwm_top1 set the top_value for note D4 USING formula
 //pwm_top2 set the top_value for note E4 USING formula
 //pwm_top3 set the top_value for note F4 USING formula 
 //pwm_top4 set the top_value for note G4 USING formula
 //pwm_top5 set the top_value for note A4 USING formula
 //pwm_top6 set the top_value for note B4 USING formula


//Interrupt service routine is enabled whenver there is output compare match OCR1X 
//Varing pwm_top value inorder to create sinusiodal wave ,
//Input compare register ICR  sets timeperiod i.e pwm_frequency (top_value of trianglar wave )
//whenver there is output compare match ,OCR1X is updated and increased upto PWM_FREQUENCY
//and decremented after reaching the top value  of ICR

ISR(TIMER1_COMPA_vect)
{
  unsigned int pwm_top0;
  if(bit_is_set(PINC,0))
    {
      pwm_top0= (160000000/(8*C4))-1;
if(OCR1A<=pwm_top0)
  OCR1A=OCR1A+1;
else
  OCR1A=OCR1A-1;
    }
 
    unsigned int pwm_top1;
 if(bit_is_set(PINC,1))
    {
      pwm_top1= (160000000/(8*D4))-1;
if(OCR1A<=pwm_top1)
  OCR1A=OCR1A+1;
else
  OCR1A=OCR1A-1;
    }
    
    unsigned int pwm_top2;
 if(bit_is_set(PIND,2))
    {
      pwm_top2 = (160000000/(8*E4))-1;
if(OCR1A<=pwm_top2)
  OCR1A=OCR1A+1;
else
  OCR1A=OCR1A-1;
    }
    
    unsigned int pwm_top3;
  
 if(bit_is_set(PIND,3))
    {
      pwm_top3= (160000000/(8*F4))-1;
if(OCR1A<=pwm_top3)
  OCR1A=OCR1A+1;
else
  OCR1A=OCR1A-1;
    }
    
    unsigned int pwm_top4;
    
  if(bit_is_set(PIND,4))
    {
      pwm_top4= (160000000/(8*G4))-1;
if(OCR1A<=pwm_top4)
  OCR1A=OCR1A+1;
else
  OCR1A=OCR1A-1;
    }
   unsigned int pwm_top5;
    
  if(bit_is_set(PIND,5))
    {
      pwm_top5= (160000000/(8*A4))-1;
if(OCR1A<=pwm_top5)
  OCR1A=OCR1A+1;
else
  OCR1A=OCR1A-1;
    }
     unsigned int pwm_top6;
    
  if(bit_is_set(PIND,6))
    {
      pwm_top6= (160000000/(8*B4))-1;
if(OCR1A<=pwm_top6)
  OCR1A=OCR1A+1;
else
  OCR1A=OCR1A-1;
    }
    
}


//FUNCTION NAME : play_note

//INPUT: top_value & duration as unsigned int 
//duration gives the time for which note to be played in millisec

//LOGIC : reseting timer counter to zero,and store top_value in the input compare register
//and emable the output compare match interrupt
//Also, setting the prescalar to start timer and wait till note to played for given duartion
//resetting prescalar to stop timer after respective note is played

//EXAMPLE CALL: play_note(435,200)

void play_note(unsigned int top_value ,unsigned int duration)
{
  // Reset the 16 bit Counter
   TCNT1H = 0;
   TCNT1L = 0;
   //emable the output compare match interrupt
   TIMSK1|=1<<OCIE1A;
   // enable the global interrupt
    sei();
   // Set the Counter TOP
   ICR1H = ( top_value >> 8 ) & 0xFF;
   ICR1L = top_value;
   
//function call to start timer by setting prescalar
   pwm_set();
//Wait for which note to be played
   _delay_ms(duration);
//resetting prescalar
   pwm_stop();
   _delay_ms(pause);
 //disenable the interrupt
   cli();
     
}



//FORMULA USED:_
//pwm frequency =clock_frequency/[prescalar*(top+1)] 
//pwm_topX=[16000000/prescalar*(pwm frequency)]-1


 //pwm_top0 set the top_value for note C4 USING formula
 //pwm_top1 set the top_value for note D4 USING formula
 //pwm_top2 set the top_value for note E4 USING formula
 //pwm_top3 set the top_value for note F4 USING formula 
 //pwm_top4 set the top_value for note G4 USING formula
 //pwm_top5 set the top_value for note A4 USING formula
 //pwm_top6 set the top_value for note B4 USING formula


//main function
//DESCRIPTION:  Setting pwm ~ pin 9 as output
//PORT D AND PORT C AS INPUT FOR PUSH BUTTONS
//INTIALIZE TIMER FOR SETTING PWM 
//duration gives the time for which note to be played in millisec and is set to 2000 ms i.e 2 sec.
//LOGIC:-  As each push button is pressed ,respective note is called and played in speaker(8 ohm)
//The function play_note for each note will generate sinusoidal wave and give it as a input to speaker

 int main()
 {
  
  unsigned int pwm_top0,pwm_top1,pwm_top2,pwm_top3,pwm_top4,pwm_top5,pwm_top6;
   
 //Setting pwm ~ pin 9 as output 
    DDRB|=1<<PINB1;
 //PORT D AND PORT C AS INPUT FOR PUSH BUTTONS
    DDRD=0X00;
    DDRC=0X00;
  timer1_initialize();

 while(1) 
  {
    //if((PINC & (1<<PINC0))==1)  //IF BUTTON 1 IS PRESSED
    if(bit_is_set(PINC,0))
    { PORTC=0X01;
     pwm_top0= (160000000/(8*C4))-1;
  play_note(pwm_top0,2000);
    }

    
    if(bit_is_set(PINC,1))//IF BUTTON 2 IS PRESSED
    { PORTC=0X02;
     pwm_top1= (160000000/(8*D4))-1;
  play_note(pwm_top1,2000);
    }

    
    if(bit_is_set(PIND,2))//IF BUTTON 3 IS PRESSED
    { PORTD=0X04;
     pwm_top2= (160000000/(8*E4))-1;
  play_note(pwm_top2,2000);
    }

    
    if(bit_is_set(PIND,3))//IF BUTTON 4 IS PRESSED
    { PORTD=0X08;
     pwm_top3= (160000000/(8*F4))-1;
  play_note(pwm_top3,2000);
    }

    
    if(bit_is_set(PIND,4))//IF BUTTON 5 IS PRESSED
    { PORTD=0X10;
     pwm_top4= (160000000/(8*G4))-1;
  play_note(pwm_top4,2000);
    }

    
    if(bit_is_set(PIND,5))//IF BUTTON 6 IS PRESSED
    { PORTD=0X20;
     pwm_top5= (160000000/(8*A4))-1;
  play_note(pwm_top5,2000);
    }

    
    if(bit_is_set(PIND,6))//IF BUTTON 7 IS PRESSED
    { PORTD=0X40;
     pwm_top6= (160000000/(8*B4))-1;
  play_note(pwm_top6,2000);
    }
    
  }
    
 }
