#define CS	 6  //Pin 13 as chip selection output
#define WR	 7  //Pin 12 as read clock	output
#define DATA 8	//Pin 7 as Serial data output

#define CS1    digitalWrite(CS, HIGH)
#define CS0    digitalWrite(CS, LOW)
#define WR1    digitalWrite(WR, HIGH)
#define WR0    digitalWrite(WR, LOW)
#define DATA1  digitalWrite(DATA, HIGH)
#define DATA0  digitalWrite(DATA, LOW)


#define sbi(x, y)  (x |= (1 << y))
#define cbi(x, y)  (x &= ~(1 <<y ))
#define uchar   unsigned char
#define uint   unsigned int

//定义HT1621的命令
#define  ComMode    0x52  //4COM,1/3bias  1000    010 1001  0
#define  RCosc      0x30  //1000 0011 0000
#define  LCD_on     0x06  //1000     0000 0 11 0
#define  LCD_off    0x04
#define  Sys_en     0x02  //1000   0000 0010
#define  CTRl_cmd   0x80
#define  Data_cmd   0xa0


/*0,1,2,3,4,5,6,7,8,9,A,b,C,c,d,E,F,H,h,L,n,N,o,P,r,t,U,-, ,*/

const char num_old[]={0x7D,0x60,0x3E,0x7A,0x63,0x5B,0x5F,0x70,0x7F,0x7B,0x77,0x4F,0x1D,0x0E,0x6E,0x1F,0x17,0x67,0x47,0x0D,0x46,0x75,0x37,0x06,0x0F,0x6D,0x02,0x00,};
                 //0      1      2      3        4      5      6       7       8       9
char dispnum[6]={0x00,0x00,0x00,0x00,0x00,0x00};

//                0     1     2     3     4     5     6     7     8     9     ^o    o
const char num[]={0x3f, 0x09, 0x67, 0x4f, 0x59, 0x5e, 0x7e, 0x0b, 0x7f, 0x5f, 0x53, 0x6C};

char cara[127];

void charSet(){
  cara['a'] = 0x6F;
  cara['b'] = 0x7C;
  cara['c'] = 0x64;
  cara['d'] = 0x6D;
  cara['e'] = 0x77;
  cara['f'] = 0x72;
  cara['g'] = 0x5F;
  cara['h'] = 0x78;
  cara['i'] = 0x20;
  cara['j'] = 0x0C;
  cara['k'] = 0x7A;
  cara['l'] = 0x30;
  cara['m'] = 0x28;
  cara['n'] = 0x68;
  cara['o'] = 0x6C;
  cara['p'] = 0x73;
  cara['q'] = 0x5B;
  cara['r'] = 0x60;
  cara['s'] = 0x5E;
  cara['t'] = 0x74;
  cara['u'] = 0x2C;
  cara['v'] = 0x2C;
  cara['w'] = 0x28;
  cara['x'] = 0x79;
  cara['y'] = 0x5D;
  cara['z'] = 0x67;

  cara['A'] = 0x7B;
  cara['B'] = 0x7F;
  cara['C'] = 0x36;
  cara['D'] = 0x6D;
  cara['E'] = 0x76;
  cara['F'] = 0x72;
  cara['G'] = 0x3E;
  cara['H'] = 0x79;
  cara['I'] = 0x30;
  cara['J'] = 0x2D;
  cara['K'] = 0x7A;
  cara['L'] = 0x34;
  cara['M'] = 0x2A;
  cara['N'] = 0x3B;
  cara['O'] = 0x3F;
  cara['P'] = 0x73;
  cara['Q'] = 0x57;
  cara['R'] = 0x33;
  cara['S'] = 0x5E;
  cara['T'] = 0x74;
  cara['U'] = 0x3D;
  cara['V'] = 0x3D;
  cara['W'] = 0x15;
  cara['X'] = 0x79;
  cara['Y'] = 0x5D;
  cara['Z'] = 0x67;

  cara['*'] = 0x53;
  cara['-'] = 0x40;
  cara['/'] = 0x61;
  cara['='] = 0x44;
  cara['\''] = 0x01;


}

void SendBit_1621(uchar sdata,uchar cnt)
{
	//data cnt HT1621
	uchar i;
	for(i=0;i<cnt;i++)
	{
		WR0;
		if(sdata&0x80) DATA1;
		else DATA0;
		WR1;
		sdata<<=1;
	}
}

void SendCmd_1621(uchar command)
{
	CS0;
	SendBit_1621(0x80,4);
	SendBit_1621(command,8);
	CS1;
}

void Write_1621(uchar addr,uchar sdata)
{
	addr<<=2;
	CS0;
	SendBit_1621(0xa0,3);
	SendBit_1621(addr,6);
	SendBit_1621(sdata,8);
	CS1;
}

void HT1621_all_off(uchar num)
{
	uchar i;
	uchar addr=0;
	for(i=0;i<num;i++)
	{
		Write_1621(addr,0x00);
		addr+=2;
	}
}

void HT1621_all_on(uchar num)
{
	uchar i;
	uchar addr=0;
	for(i=0;i<num;i++)
	{
		Write_1621(addr,0xff);
		addr+=2;
	}
}

void Init_1621(void)
{
	SendCmd_1621(Sys_en);
	SendCmd_1621(RCosc);
	SendCmd_1621(ComMode);
	SendCmd_1621(LCD_on);
}

void displaydata(int p)
{
	uchar i=0;
	switch(p)
	{
		case 1:
		sbi(dispnum[0],7);
		break;
		case 2:
		sbi(dispnum[1],7);
		break;
		case 3:
		sbi(dispnum[2],7);
		break;
		default:break;
	}
	for(i=0;i<=5;i++)
	{
		Write_1621(i*2,dispnum[i]);
	}
}



void draw_nb(uint8_t dig, uint8_t value){

  Write_1621(6,bitRead(value, 6) * (16 * dig) + bitRead(value, 7)*dig);
  Write_1621(4,bitRead(value, 5) * (16 * dig) + bitRead(value, 4)*dig);
  Write_1621(2,bitRead(value, 3) * (16 * dig) + bitRead(value, 2)*dig);
  Write_1621(0,bitRead(value, 1) * (16 * dig) + bitRead(value, 0)*dig);
}

void draw_s(String s){
  switch(s.length()){
    case 0:
      draw(0,0,0,0);
      break;
    case 1:
      draw(0,0,0,cara[s.charAt(0)]);
      break;
    case 2:
      draw(0,0,cara[s.charAt(0)],cara[s.charAt(1)]);
      break;
    case 3:
      draw(0,cara[s.charAt(0)],cara[s.charAt(1)],cara[s.charAt(2)]);
      break;
    case 4:
      draw(cara[s.charAt(0)],cara[s.charAt(1)],cara[s.charAt(2)],cara[s.charAt(3)]);
      break;
    default:
      draw(0,0,0,0);
      break;
  }
}

unsigned int pow_n [] = { 1, 10, 100, 1000, 10000 } ;

int ExtractDigit(int V, int P)
{
  return V / pow_n[P] % 10 ;
}

void draw_n(int n){
  if(n < 1)
    draw(0,0,0,0);
  if(n >= 0 && n < 10)
    draw(0,0,0,num[n]);
  if(n >= 10 && n < 100){
    draw(0,0,num[ExtractDigit(n,1)],num[ExtractDigit(n,0)]);
  }
  if(n >= 100 && n < 1000){
    draw(0,num[ExtractDigit(n,2)],num[ExtractDigit(n,1)],num[ExtractDigit(n,0)]);
  }
  if(n >= 1000 && n < 10000){
    draw(num[ExtractDigit(n,3)],num[ExtractDigit(n,2)],num[ExtractDigit(n,1)],num[ExtractDigit(n,0)]);
  }
  if(n >= 10000)
    draw_s("Err");
}

void draw(uint8_t dig1, uint8_t dig2, uint8_t dig3, uint8_t dig4){

  // --2--
  //5     1
  //|--7--|
  //6     4
  // --3--
  // numero 5 = B01011110 = 0x54 = 94

  uint8_t raw6 = ((bitRead(dig1, 6) * 16 *8 ) + (bitRead(dig2, 6) * 16*4 ) +
  (bitRead(dig3, 6) * 16*2) + (bitRead(dig4, 6) * 16) +
  bitRead(dig1, 7)*8 + bitRead(dig2, 7)*4 + bitRead(dig3, 7)*2 + bitRead(dig4, 7));

  uint8_t raw4 = ((bitRead(dig1, 5) * 16 *8) + (bitRead(dig2, 5) * 16*4 ) +
  (bitRead(dig3, 5) * 16*2) + (bitRead(dig4, 5) * 16) +
  bitRead(dig1, 4)*8 + bitRead(dig2, 4)*4 + bitRead(dig3, 4)*2 + bitRead(dig4, 4));

  uint8_t raw2 = ((bitRead(dig1, 3) * 16 *8) + (bitRead(dig2, 3) * 16*4 ) +
  (bitRead(dig3, 3) * 16*2) + (bitRead(dig4, 3) * 16) +
  bitRead(dig1, 2)*8 + bitRead(dig2, 2)*4 + bitRead(dig3, 2)*2 + bitRead(dig4, 2));

  uint8_t raw0 = ((bitRead(dig1, 1) * 16 *8) + (bitRead(dig2, 1) * 16*4 ) +
  (bitRead(dig3, 1) * 16*2) + (bitRead(dig4, 1) * 16) +
  bitRead(dig1, 0) * 8 + bitRead(dig2, 0)* 4 + bitRead(dig3, 0)*2 + bitRead(dig4, 0));
  Write_1621(6,raw6);
  Write_1621(4,raw4);
  Write_1621(2,raw2);
  Write_1621(0,raw0);
}

void setup() {
  pinMode(CS, OUTPUT); //
  pinMode(WR, OUTPUT); //
  pinMode(DATA, OUTPUT); //
  CS1;
  DATA1;
  WR1;
  delay(50);
  Init_1621();
  HT1621_all_on(16); //1621
  delay(100);
  HT1621_all_off(16); //1621
  delay(100);

  charSet();

  //frog face
  Write_1621(0,0x66);
  Write_1621(2,0x1f);
  Write_1621(4,0x86);
  Write_1621(6,0x60);

  HT1621_all_off(16);

  draw(num[0],num[1],num[2],num[3]);
  draw_s("err");

  draw_n(123);

}

void loop() {

 // you can place your main code here to run repeatedly

}
