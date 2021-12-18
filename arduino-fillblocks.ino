// Code by Mischa Spelt - Dec 2020

// 2-dimensional array of row pin numbers:
int R[] = {5, 4, 3, 2, 6, 7, 8, 9};
//int R[] = {2, 3, 4, 5, 6, 7, 8, 9};
// 2-dimensional array of column pin numbers:
int C[] = {A0, A1, A2, A3, A4, A5, A6, A7};

unsigned char display[8][8] = {0};

void setup()
{
  // iterate over the pins:
  for (int i = 0; i < 8; i++)
    // initialize the output pins:
  {
    pinMode(R[i], OUTPUT);
    pinMode(C[i], OUTPUT);
  }
}

void loop()
{
  fill();
  Delay(display, 1000);
  empty();
}

void fillRow(int row, int isOn) 
{
  for(int c = 0; c < 8; ++c )
  {
    display[row][c] = isOn;
  }
}

void fill() 
{
  for(int row = 7; row >= 0; --row)
  {
    for(int falling = 0; falling <= row; ++falling) 
    {
      fillRow(falling, 1);
      Delay(display, 10);
      fillRow(falling, 0);
    }

    fillRow(row, 1);
    Delay(display, 100);
  }
}

void empty()
{
  double fallDelay = 50;
  for(int col = 7; col >= 0; --col)
  {
    display[7][col] = 0;
    Delay(display, fallDelay);
    display[7][col] = 1;
       
    for(int falling = 0; falling < 8; ++falling) 
    {
      display[falling][col] = 0;
      Delay(display, fallDelay);
    }

    fallDelay *= 0.8;
  }

  Delay(display, 1000);
}

void Delay(unsigned char display[8][8], double duration)
{
  while(duration > 0) 
  {
    Display(display);
    duration -= 8; // Display takes about 8 ms
  }
}

void Display(unsigned char display[8][8])
{
  for (int c = 0; c < 8; c++)
  {
    digitalWrite(C[c], LOW); //use the column
    //loop
    for (int r = 0; r < 8; r++)
    {
      digitalWrite(R[r], display[r][c]);
    }

    delay(1);
    Clear();  //Remove empty display light
  }
}

void Clear()
{
  for (int i = 0; i < 8; i++)
  {
    digitalWrite(R[i], LOW);
    digitalWrite(C[i], HIGH);
  }
}
