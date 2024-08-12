#include <FastLED.h>
#include <SoftwareSerial.h>

   /***MATRIX MACROS***/

#define LED_TYPE       NEOPIXEL
#define COLOR_ORDER    GRB
#define WIDTH          8
#define HEIGHT         10
#define NUM_LEDS       80
#define DATA_PIN       4
#define MAX_SPEED      475
#define RX_PIN         2
#define SENSOR_PIN     0
#define SOUND_SENSE    1005
#define SNAKE_LENGTH   6 // Define the length of the snake

/***BASIC COLORS ***/
#define  BLUE         CRGB(0, 0, 255)
#define  GREEN        CRGB(0, 255, 0)
#define  RED          CRGB(255, 0, 0)
#define  BLACK        CRGB(0, 0, 0)

    /****COLORS****/
#define RED_COLOR     'A'
#define GREEN_COLOR   'B'
#define BLUE_COLOR    'C'
#define PINK_COLOR    'E'
#define WHITE_COLOR   'F'
#define YELLOW_COLOR  'D'
#define CYAN_COLOR    'G' // LBNI
    /****ALL MOVE ****/
#define RANDOM          'c'
#define ALL_UP          'd'   //ledsfrom dowen to up 
#define ALL_DOWN        '#'    //ledsfrom up to DOWEN 
#define ALL_LEFT        'e'
#define ALL_RIGHT       '$'
    /***ROW & COLOM***/
#define ONE_ROW_UP      'k'
#define ONE_ROW_DOWN    'K'  
#define ONE_COLOM_LEFT  'j'
#define ONE_COLOM_RIGHT '@'
  /***DOT***/
#define ONE_DOT_RIGHT   'l' 
#define ONE_DOT_LEFT    'L'
#define ONE_DOT_UP      'm'
#define ONE_DOT_DOWN    'M'
    /***SHAPES***/
#define SNAKE_SHAPE     'n'
#define DOUBLE_SNAKE    'o'
#define SQUARE_SHAPE    'g'
#define DOUBLE_SQUARE   'h'
#define TRIANGLE_SHAPE  'f'
#define CORNER_1        'a'
#define CORNER_2        'b'
    /***ADC SHAPES***/
#define  ADC_ALL        'y' 
#define  ADC_RANDOM     'p'
#define  ADC_UP         'q'
#define  ADC_DOWN       't'
#define  ADC_R_L        'r'
#define  ADC_L_R        'u'
#define  ADC_ALL_2      'v'
#define  ADC_SNAKE      's'
#define  ADC_HOME       'w'
/****STOP_SHAPES**/
#define STOP            '!'
 

SoftwareSerial mySerial(RX_PIN, 1);
CRGB leds[NUM_LEDS];
  CRGB Color1 =  CRGB(0,0,200);  // Yellow color for the first 2 rows
  CRGB Color2 =  CRGB(0,200,0);  // Purple color for the rest of the rows
  CRGB Color3 = CRGB(200,0,0);    // Blue color for the last row
int SENSOR_pin = A1;  // input pin for the potentiometer
    uint32_t valueAfterH=0;
   uint32_t Real_value=0;
  uint8_t receivedChar ;
  uint32_t Color=0xff0000;
   volatile uint16_t Temp_recive=0;
   unsigned long previousMillis = 0; // Store the last time the LED was updated
long interval = 100;        // Interval at which to update (milliseconds)
int currentCol = 0; 
signed char currentRow =0; 
  int triangleBase = 2; 
int triangleHeight = 2;     // Initial height of the triangle
bool growing = true;
uint16_t Read_sensor;
 static char prevChar = '\0';
 uint16_t butern_recive =0;
 volatile uint16_t receivedByte=0;
  int squareSize = 2; 
  int currentRow_1 = 0;
volatile bool H_Detected = false; // Flag to indicate 'H' was detected
volatile char H_Buffer[10]; // Buffer to store numeric characters after 'H'
volatile int H_BufferIndex = 0; // Index for the buffer
volatile bool dataReady = false; // Flag to indicate a complete number after 'H' is ready
bool filling = false ;
volatile int extractedValue = 0; // The extracted value after 'H'

int snake[80];  // Stores the position of each segment of the snake
int targetLED;
int snakeColorIndex = 0;
CRGB colors[] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Cyan};
int colorIndex ;
int direction = -WIDTH;  
int currentLED = NUM_LEDS-1;
 int currentRow_2 =HEIGHT-1;
 int currentColom_2= WIDTH-1;
   int currentColom_1= 0;
   int signed currentLedIndex = NUM_LEDS - 1;
   bool ledsInitialized= false ;
   bool allOff = false;
   bool initialized = false;
   int pyramidApex = HEIGHT - 1;  // Start with the apex at the bottom
byte counter=0;
 int ADC_value;       
  unsigned long     currentMillis = millis();
int read_value_1 = 0;
void timer2_config()
 {
   TCCR2A = 0; // Clear Control Register A
  TCCR2B = 0; // Clear Control Register B
  TCNT2  = 0; // Initialize counter value to 0

  // Set compare match register for 10ms increments
  OCR2A = 78; // = (16*10^6) / (1024*100) - 1 (must be <256)

  // Turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS22, CS21 and CS20 bits for 1024 prescaler
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); 
  // Enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);

  // Enable global interrupts
  sei();
 } 

void setup() {
 
  FastLED.addLeds<LED_TYPE, DATA_PIN>(leds, NUM_LEDS);
  timer2_config();
  pinMode(RX_PIN, INPUT);
  pinMode(SENSOR_PIN, INPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
 

}

void loop() {

  //int ADC_value = analogRead(SENSOR_PIN);
 if (dataReady) {
    dataReady = false; // Reset the flag
    
    // Use the extracted value
    int Real_value = MAX_SPEED - extractedValue;
    
    // Print the real value for debugging
    Serial.print("Real value 'H': ");
    Serial.println(Real_value);
    interval=Real_value;
  }


 switch (receivedChar) 
  {
        case RED_COLOR :
          
            Color = 0xFF0000; //RED  
        
     break;

     case GREEN_COLOR :
         
            Color = 0x00FF00; //GREEN
           
          
     break;

     
     case BLUE_COLOR :
          
            Color = 0x00008B; //BLUE     
     break;

     case PINK_COLOR :
         
            Color = 0xFF1493; //PINK
            
     break;
     case WHITE_COLOR :
     
            Color = 0xFFFAF0; //WHITE
           
         
     break;
     case YELLOW_COLOR :
     
            Color = 0xFFD700; //YELLOW
           
          
     break;
     case CYAN_COLOR :
     
            Color = 0x87CEFA; //CYAN
            
        
          
     break;

     default:
     break;
  }

    if((receivedChar != RED_COLOR) && (receivedChar != GREEN_COLOR) && (receivedChar != BLUE_COLOR ) && (receivedChar != PINK_COLOR) && (receivedChar != WHITE_COLOR)&& (receivedChar != YELLOW_COLOR) &&(receivedChar != CYAN_COLOR)  )
    {
      butern_recive = receivedChar;
    }

switch (butern_recive) 
  {

      case RANDOM:

           Random();

       break;
       
      case SNAKE_SHAPE:

         Snake_Bottom_Left_to_Top_Right();
           
       break;

      case SQUARE_SHAPE:

         Moving_Square_3x3();
           
       break;

      case DOUBLE_SQUARE:

         Moving_Two_Squares();
           
       break;

      case TRIANGLE_SHAPE:

           Triangle_Bottom_to_Top();
           
       break;

      case DOUBLE_SNAKE:

           Double_Snake_Bottom_Left_to_Top_Right();
           
       break;

      case CORNER_1:
        
       growShrinkDiagonal_22();
            
       break;

      case CORNER_2:

        newDiagonal();
       // GrowShrinkDiagonal_5();
           
       break;

      case ONE_DOT_UP:

          oneDotUp();

       break;

      case ONE_DOT_DOWN:

           
           OneDotDown();

       break;

       case ONE_DOT_RIGHT :
          //oneDotLeftToRight();
           One_Dot_Right();

       break;
       case ONE_DOT_LEFT :

        One_Dot_Left();
        //oneDotLeft();

       break;

       case ALL_LEFT:

           Left_to_Right() ;

       break;

       case ALL_RIGHT:

           Right_to_Left();

       break;

      case ALL_UP:

           Bottom_to_Top();

       break;

      case ALL_DOWN:

          Top_to_Bottom();
         //adc_top_to_bottom_1();


       break;

       case ONE_ROW_DOWN:

        Top_to_Bottom_Single_Row();   

       break;

       case ONE_ROW_UP:

         Bottom_to_Top_Single_Row();

       break;

       case ONE_COLOM_LEFT:
       
        Left_to_Right_Single_Colom();

       break;

       case ONE_COLOM_RIGHT:

         Right_to_Left_Single_Colom();

       break;

        case ADC_ALL:  // the bug is here/******************************************************************/

            
          initializeLeds_2();  

       break;

        case ADC_UP:        
        
            ADC_Bottom_to_Top();
         
         
          
        // adc_bottom_to_top_1();
         
                  
       break;

        case ADC_DOWN:
  
          ADC_DOWNUP();
       // ADC_Top_to_Bottom() ;
      // adc_top_to_bottom_1();
   
  

       break;

      case ADC_R_L:

        ADC_Right_to_Left() ;

       break;

      case ADC_L_R:

         ADC_Left_to_Right();

       break;

      case ADC_SNAKE:

         Read_sensor = analogRead(SENSOR_PIN);
         Serial.println(Read_sensor);
         if(Read_sensor <SOUND_SENSE )
         {
            Snake_Bottom_Left_to_Top_Right();
         }

       break;
        case ADC_ALL_2:

         Read_sensor = analogRead(SENSOR_PIN);
         Serial.println(Read_sensor);
         if(Read_sensor <SOUND_SENSE )
         {
          ADC_Zigag_snake();
         
         }
    
       break;

      case ADC_RANDOM: 
      
        ADC_equalizer();

       break ;

      case ADC_HOME:
          
         Read_sensor = analogRead(SENSOR_PIN);
         if(Read_sensor <SOUND_SENSE )
         {
          Snake_Game();
         
         }
       break ;

      case STOP:

        fill_solid(leds, NUM_LEDS, CRGB::Black);
         FastLED.clear();
        FastLED.show();
       
    
       break;
        

  }
}

 
 
  ISR(TIMER2_COMPA_vect) 
{ // tick every 10 mili
    while (mySerial.available()) {
     receivedChar = mySerial.read();
    
    if (H_Detected)
    {
      if (isdigit(receivedChar)) 
      {
        H_Buffer[H_BufferIndex++] = receivedChar; // Store numeric characters
        if (H_BufferIndex >= sizeof(H_Buffer) - 1)
        {
          H_BufferIndex = sizeof(H_Buffer) - 1; // Prevent buffer overflow
        }
      } 
      else 
      {
        H_Buffer[H_BufferIndex] = '\0'; // Null-terminate the string
        extractedValue = atoi(H_Buffer); // Convert to integer
        dataReady = true; // Set the flag to indicate data is ready
        H_BufferIndex = 0; // Reset the buffer index for the next message
        H_Detected = false; // Reset the flag
      }
    }

    if (receivedChar == 'H') 
    {
      H_Detected = true; // Set the flag to indicate 'H' was detected
      H_BufferIndex = 0; // Reset the buffer index for a new number
    }
  }

}
void oneDotLeftToRight() {
  static int currentRow = 0;
  static int currentColumn = 0;
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time the dot moved
    previousMillis = currentMillis;

    // Clear the previous LED
    FastLED.clear();

    // Calculate the index of the current LED
    int index;
    if (currentRow % 2 == 0) {
      index = currentRow * WIDTH + currentColumn;
    } else {
      index = currentRow * WIDTH + (WIDTH - 1 - currentColumn);
    }

    // Set the current LED to the specified color
    leds[index] = Color;

    // Show the updated LEDs
    FastLED.show();

    // Update the column for the next frame
    currentColumn++;
    if (currentColumn >= WIDTH) {
      currentColumn = 0;
      currentRow++;
      if (currentRow >= HEIGHT) {
        currentRow = 0;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////
void ADC_DOWNUP()
{
  for(int i=0;i<3;i++)
   {
   ADC_value = analogRead(SENSOR_PIN);
    read_value_1 += ADC_value;
   }
   Serial.println("Step");
   

   read_value_1 /=4 ;
Serial.println(read_value_1);
      if (read_value_1 > SOUND_SENSE)
      {
        counter--;
        //Serial.println("Step");
         if (counter < 0)
             {
              counter = -1 ;
              }
      }
        else 
        {
          counter++;
          if (counter > 10)
             {
              counter =  10;
              }
        }

        for (int i=0; i <= counter; i++)
        {setRow_0(i, CRGB::Green);} // change 
        for(int i=counter+1; i < 10 ; i++)
        setRow_0(i, CRGB::Black);

        Serial.print("read_value_1 =");
        Serial.println(read_value_1);
        Serial.print("Counter =");
         Serial.println(counter);
      FastLED.show();
      //delay(100);
}

void oneDotLeft() {
  static int currentRow = 0;
  static int currentColumn = WIDTH - 1;
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time the dot moved
    previousMillis = currentMillis;

    // Clear the previous LED
    FastLED.clear();

    // Calculate the index of the current LED
    int index;
    if (currentRow % 2 == 0) {
      index = currentRow * WIDTH + currentColumn;
    } else {
      index = currentRow * WIDTH + (WIDTH - 1 - currentColumn);
    }

    // Set the current LED to the specified color
    leds[index] = Color;

    // Show the updated LEDs
    FastLED.show();

    // Update the column for the next frame
    currentColumn--;
    if (currentColumn < 0) {
      currentColumn = WIDTH - 1;
      currentRow++;
      if (currentRow >= HEIGHT) {
        currentRow = 0;
      }
    }
  }
}

void oneDotUp() {
  static int currentColumn = WIDTH - 1;
  static int currentRow = HEIGHT - 1;
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time the dot moved
    previousMillis = currentMillis;

    // Clear all LEDs
    FastLED.clear();

    // Calculate the correct index for the LED
    int index;
    if (currentRow % 2 == 0) {
      index = currentRow * WIDTH + currentColumn;
    } else {
      index = currentRow * WIDTH + (WIDTH - 1 - currentColumn);
    }

    // Set the LED to the specified color
    leds[index] = Color;

    // Show the updated LEDs
    FastLED.show();

    // Move to the next position
    currentRow--;
    if (currentRow < 0) {
      currentRow = HEIGHT - 1;
      currentColumn--;
      if (currentColumn < 0) {
        currentColumn = WIDTH - 1; // Restart from the rightmost column
      }
    }
  }
}

void OneDotDown() {
  static int currentColumn = 0;
  static int currentRow = 0;
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time the dot moved
    previousMillis = currentMillis;

    // Clear all LEDs
    FastLED.clear();

    // Calculate the correct index for the LED
    int index;
    if (currentRow % 2 == 0) {
      index = currentRow * WIDTH + currentColumn;
    } else {
      index = currentRow * WIDTH + (WIDTH - 1 - currentColumn);
    }

    // Set the LED to the specified color
    leds[index] = Color;

    // Show the updated LEDs
    FastLED.show();

    // Move to the next position
    currentRow++;
    if (currentRow > HEIGHT - 1) {
      currentRow = 0;
      currentColumn++;
      if (currentColumn > WIDTH-1) {
        currentColumn = 0; // Restart from the rightmost column
      }
    }
  }
}

void initializeLeds_2() {
  unsigned long currentMillis = millis();
  int adcValue = analogRead(SENSOR_PIN);
static int index=0 ;
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

     auto getRandomColor = []() {
      switch (random(4)) {
        case 0: return CRGB::Red;
        case 1: return CRGB::Green;
        case 2: return CRGB::Blue;
        case 3: return CRGB::White;
      }
      return CRGB::Black; // Default to black (though this shouldn't be reached)
    };
    // Initialize the LEDs with random colors if not initialized
    if (!initialized) {
      for (int i = 0; i < WIDTH-1; i++){
        if(i%2==0){
         
              setColumn(i, colors[index]);
              index++;
        }
        else
        {
          setColumn(i, colors[index+1]);
          if(index==5)
          {
            index=0 ;
          }
        }
        
        
      }
      /*for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = getRandomColor();
      }*/
      FastLED.show();
      initialized = true;
    } else {
      // If the ADC value is greater than a threshold and not all LEDs are off
      if (adcValue < SOUND_SENSE && !allOff) {
        if (currentLedIndex >= 0) {
          leds[currentLedIndex] = CRGB::Black;
          currentLedIndex--;
        } else {
          allOff = true;  // All LEDs are now off
        }
      } else {
        // Change colors of all LEDs that are still on
        for (int i = 0; i <= currentLedIndex; i++) {
          leds[i] = getRandomColor();
        }
      }

      // Reinitialize the LEDs with random colors if ADC value changes and all LEDs are off
      if (adcValue >= SOUND_SENSE && allOff) {
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = getRandomColor();
        }
        currentLedIndex = NUM_LEDS - 1;
        allOff = false;
      }

      FastLED.show();
    }
  }
}




void  ADC_Right_to_Left() {  
 
  unsigned long currentMillis = millis();
 int adcValue = analogRead(SENSOR_PIN);
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    Serial.println(adcValue);

  if (adcValue < SOUND_SENSE) {
      filling = true;
    } else {
      filling = false;
    }
        
    if (filling) {
      setColumn(currentColom_2, Color);  // Change color if needed
      currentColom_2--;
      if (currentColom_2 <= 0 ) {
        filling = false;
        currentColom_2 = 0;
      }
    } else {
      setColumn(currentColom_2, CRGB::Black);  // Turn off the current row
      currentColom_2++;
      if (currentColom_2 >= WIDTH) {
        filling = true;
        currentColom_2 = WIDTH-1;
      }
    }

    FastLED.show();
  }
}

void  ADC_Left_to_Right() {  
 
  unsigned long currentMillis = millis();
 int adcValue = analogRead(SENSOR_PIN);
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    
Serial.println(adcValue);
  if (adcValue < SOUND_SENSE) {
      filling = true;
    } else {
      filling = false;
    }
        
    if (filling) {
      setColumn(currentColom_1, Color);  // Change color if needed
      currentColom_1++;
      if (currentColom_1 >= WIDTH ) {
        filling = false;
        currentColom_1 = WIDTH-1;
      }
    } else {
      setColumn(currentColom_1, CRGB::Black);  // Turn off the current row
      currentColom_1--;
      if (currentColom_1 <= 0) {
        filling = true;
        currentColom_1 = 0;
      }
    }

    FastLED.show();
  }
}
void ADC_Bottom_to_Top() {  
 
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
     int adcValue = analogRead(SENSOR_PIN);
     static int counter =0;
      if(adcValue<SOUND_SENSE)
      {
        
        setRow(counter, CRGB::Green);
        counter++;
        if (counter==HEIGHT-1)
        {
          counter=0 ;
        }
      }
      else 
      {
        setRow(counter, CRGB::Black);
        counter--;
         if (counter==0)
        {
          counter=HEIGHT-1 ;
        }
      }

 
 /* if (read < HEIGHT-1) {
      filling = true;
    } else {
      filling = false;
    }
        
    if (filling) {
      setRow(read, Color);  // Change color if needed
      read--;
      if (read < 0) {
        filling = false;
        read = 0;
      }
    } else {
      setRow(read, CRGB::Black);  // Turn off the current row
      read++;
      if (read >= HEIGHT-1) {
        filling = true;
        read = HEIGHT-1;
      }
    }*/

    FastLED.show();
  }

}

void  ADC_Top_to_Bottom() {  
 
  unsigned long currentMillis = millis();
  int adcValue = analogRead(SENSOR_PIN);
     if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
Serial.println(adcValue);
   if (adcValue < SOUND_SENSE) {
      filling = true;
    } else {
      filling = false;
    }
    if (filling) {
      setRow(currentRow_1, Color);  // Change color if needed
      currentRow_1++;
      if (currentRow_1 >= HEIGHT) {
        filling = false;
        currentRow_1 = HEIGHT - 1;
      }
    } else {
      setRow(currentRow_1, CRGB::Black);  // Turn off the current row
      currentRow_1--;
      if (currentRow_1 < 0) {
        filling = true;
        currentRow_1 = 0;
      }
    }

    FastLED.show();
  }
}
void ADC_equalizer() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  
  int sensorValue = analogRead(SENSOR_PIN);
  Serial.println(sensorValue);
  // Check sensor value to determine whether to grow or shrink
  if (sensorValue < SOUND_SENSE) {
    growing = true;
  } else {
    growing = false;
  }

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Update pyramid apex position based on growth state
    if (growing) {
      if (pyramidApex > 0) {
        pyramidApex--; // Move the apex up
      }
    } else {
      if (pyramidApex < HEIGHT - 1) {
        pyramidApex++; // Move the apex down
      }
    }

    // Draw the pyramid
    drawPyramid(HEIGHT - pyramidApex);
    FastLED.show();
  }
}

void drawPyramid(int height) {
  // Colors for each column
  CRGB colors[WIDTH] = {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Yellow, CRGB::Cyan, CRGB::White, CRGB::Yellow, CRGB::White};

  FastLED.clear();

  // Draw the pyramid with the apex moving upwards and base expanding
  for (int row = HEIGHT - 1; row >= pyramidApex; row--) {
    int pyramidHeight = row - pyramidApex; // Distance from the apex
    int startCol = 4 - pyramidHeight;
    int endCol = 4 + pyramidHeight;
    
    for (int col = startCol; col <= endCol; col++) {
      if (col >= 0 && col < WIDTH) { // Ensure column is within bounds
        leds[row * WIDTH + col] = colors[col % WIDTH]; // Use modulo to ensure color stays in bounds
      }
    }
  }
}

void ADC_Random() {
    // Map the ADC value to the number of columns (assuming a range of 0-1023)
   

    // Set colors for the columns
    for (int i = 0; i < WIDTH/2; i++) {
        setColumn(i, CHSV(random(255),255,255));
    }
    for (int i = 4; i < WIDTH; i++) {
        setColumn(i, CRGB::White);
    }

    // Show the updated LEDs
    FastLED.show();
}

 void ADC_Zigag_snake()
 {
  static int ledIndex=NUM_LEDS-1;
    unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Turn on the current LED
    leds[ledIndex] = colors[colorIndex];
    
    // // Move to the next LED in a zigzag pattern
    // if ((currentLED / WIDTH) % 2 == 0) {
    //   // Even row: move right
    //   if (currentLED % WIDTH == WIDTH - 1) {
    //     currentLED -= WIDTH;  // Move up
    //   } else {
    //     currentLED += 1;  // Move right
    //   }
    // } else {
    //   // Odd row: move left
    //   if (currentLED % WIDTH == 0) {
    //     currentLED -= WIDTH;  // Move up
    //   } else {
    //     currentLED -= 1;  // Move left
    //   }
    // }

    //Check if we reached the top
    // if (currentLED < 0) {
    //   currentLED = NUM_LEDS -1;
    //   colorIndex = (colorIndex + 1) % (sizeof(colors) / sizeof(CRGB));
      
    // }
    
        //fill_solid(leds, NUM_LEDS, CRGB::Black);
        ledIndex--;//= NUM_LEDS - 1 - ((currentMillis / interval) % NUM_LEDS);
        if(ledIndex <0  ) {ledIndex =  NUM_LEDS-1; colorIndex = (colorIndex + 1) % (sizeof(colors) / sizeof(CRGB)); }//- SNAKE_LENGTH;
        //for (int i = 0; i < SNAKE_LENGTH; i++)
        leds[ledIndex ] = colorIndex; // Turn on the current LED


    FastLED.show();
  }
 }


void ADC_Snake() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time you updated

    static int currentRow = HEIGHT - 1;
    static int currentCol = 0;
    static bool movingRight = true;

    // Light up the current LED
    leds[currentRow * WIDTH + currentCol] =Color ;
    FastLED.show();

    // Move to the next position
    if (movingRight) {
      if (currentCol < WIDTH - 1) {
        currentCol++;
      } else {
        currentCol = WIDTH - 1;
        currentRow--;
        movingRight = false;
      }
    } else {
      if (currentCol > 0) {
        currentCol--;
      } else {
        currentCol = 0;
        currentRow--;
        movingRight = true;
      }
    }

    // If we've reached the top row, reset to start from the bottom-left
    if (currentRow < 0) {
      currentRow = HEIGHT - 1;
      currentCol = 0;
      movingRight = true;
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Clear all LEDs to start over
    }
  }
}

void GrowShrinkDiagonal_5() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time you updated

    static int step = 1;
    static bool growing = true;
    int totalSteps = (WIDTH + HEIGHT - 1);

    // Clear all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    if (growing) {
      // Growing phase
      for (int s = 1; s <= step; s++) {
        for (int i = 0; i < s; i++) {
          int row = HEIGHT - s + i;
          int col = WIDTH - i - 1;
          if (row >= 0 && col >= 0 && row < HEIGHT && col < WIDTH) {
            leds[row * WIDTH + col] = Color;
          }
        }
      }
      step++;
      if (step >= totalSteps) {
        growing = false;
        step = totalSteps;
      }
    } else {
      // Shrinking phase from top-right corner diagonally
      for (int s = 1; s <= step; s++) {
        for (int i = 0; i < s; i++) {
          int row = i;
          int col = WIDTH - s + i;
          if (row >= 0 && col >= 0 && row < HEIGHT && col < WIDTH) {
            leds[row * WIDTH + col] = Color;
          }
        }
      }
      step--;
      if (step < 1) {
        growing = true;
        step = 1;
      }
    }

    FastLED.show();
  }
}




void ColorRows() {
   static CRGB Color1 = CRGB::Yellow;  // Yellow color for the first 2 rows
  CRGB Color2 = CRGB::Purple;  // Purple color for the rest of the rows
  CRGB Color3 = CRGB::Blue;    // Blue color for the last row

  for (int row = 0; row < HEIGHT; row++) {
    if (row < 2) {
      setRow(row, Color1);
    } else if (row == HEIGHT - 1) {
      setRow(row, Color3);
    } else {
      setRow(row, Color2);
    }
  }

  FastLED.show();
}



void drawSquare() {
  static int startX = WIDTH - 1;  // Starting X position (rightmost)
  static int startY = HEIGHT - 1; // Starting Y position (bottommost)

  unsigned long currentMillis = millis();

  // Check if it's time to update the animation
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the animation was updated
    previousMillis = currentMillis;

    // Clear LEDs
    FastLED.clear();

    // Draw the square
    for (int row = startY; row > startY - squareSize; row--) {
      for (int col = startX; col > startX - squareSize; col--) {
        leds[row * WIDTH + col] = CRGB::Red;  // Set color (adjust as needed)
      }
    }

    // Show the LEDs
    FastLED.show();

    // Update square size for next frame
    if (squareSize < min(WIDTH, HEIGHT)) {
      squareSize++;   // Grow the square until it fills the matrix
    } else {
      squareSize--;   // Shrink the square back down
    }

    // Adjust starting positions when shrinking
    if (squareSize < 2) {
      startX = WIDTH - 1;
      startY = HEIGHT - 1;
    } else {
      startX = WIDTH - squareSize;
      startY = HEIGHT - squareSize;
    }
  }
}

void GrowShrinkDiagonal_2() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time you updated

    static int step = 1;
    static bool growing = true;
    int totalSteps = (WIDTH + HEIGHT - 1);

    // Clear all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    if (growing) {
      // Growing phase
      for (int s = 1; s <= step; s++) {
        for (int i = 0; i < s; i++) {
          int row = HEIGHT - s + i;
          int col = WIDTH - i - 1;
          if (row >= 0 && col >= 0) {
            leds[row * WIDTH + col] = Color;
          }
        }
      }
      step++;
      if (step >= totalSteps) {
        growing = false;
        step = totalSteps;
      }
    } else {
      // Shrinking phase
      for (int s = 1; s <= step; s++) {
        for (int i = 0; i < s; i++) {
          int row = HEIGHT - s + i;
          int col = WIDTH - i - 1;
          if (row >= 0 && col >= 0) {
            leds[row * WIDTH + col] = Color;
          }
        }
      }
      step--;
      if (step < 1) {
        growing = true;
        step = 1;
      }
    }

    FastLED.show();
  }
}
void newDiagonal() {
  static int phase = 1; // 1 for the first triangle, 2 for the second
  static int size = 1; // Current size of the diagonal line
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time the dot moved
    previousMillis = currentMillis;

    // Clear the previous frame
    FastLED.clear();

    if (phase == 1) {
      // Draw the first triangle
      for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
          int row = i - j;
          int column = WIDTH - 1 - j;

          if (row >= 0 && row < HEIGHT && column >= 0 && column < WIDTH) {
            int index;
            if (row % 2 == 0) {
              index = row * WIDTH + column;
            } else {
              index = row * WIDTH + (WIDTH - 1 - column);
            }

            leds[index] = Color;
          }
        }
      }

      size++;
      if (size > HEIGHT) {
        size = 1;
        phase = 2;
      }
    } else if (phase == 2) {
      // Draw the second triangle
      for (int i = 0; i < size; i++) {
        for (int j = 0; j <= i; j++) {
          int row = HEIGHT - 1 - (i - j);
          int column = WIDTH - 1 - (HEIGHT - 1 - j);

          if (row >= 0 && row < HEIGHT && column >= 0 && column < WIDTH) {
            int index;
            if (row % 2 == 0) {
              index = row * WIDTH + column;
            } else {
              index = row * WIDTH + (WIDTH - 1 - column);
            }

            leds[index] = Color;
          }
        }
      }

      size++;
      if (size > HEIGHT) {
        size = 1;
        phase = 1;
      }
    }

    // Show the updated LEDs
    FastLED.show();
  }
}
void GrowShrinkDiagonal_1() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time you updated

    static int step = 1;
    static bool growing = true;
    int totalSteps = (WIDTH + HEIGHT - 1);

    // Clear all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    if (growing) {
      // Growing phase
      for (int s = 1; s <= step; s++) {
        for (int i = 0; i < s; i++) {
          int row = s - i - 1;
          int col = i;
          if (row < HEIGHT && col < WIDTH) {
            leds[(HEIGHT - 1 - row) * WIDTH + col] = Color;
          }
        }
      }
      step++;
      if (step >= totalSteps) {
        growing = false;
        step = totalSteps;
      }
    } else {
      // Shrinking phase
      for (int s = 1; s <= step; s++) {
        for (int i = 0; i < s; i++) {
          int row = s - i - 1;
          int col = i;
          if (row < HEIGHT && col < WIDTH) {
            leds[(HEIGHT - 1 - row) * WIDTH + col] = Color;
          }
        }
      }
      step--;
      if (step < 1) {
        growing = true;
        step = 1;
      }
    }

    FastLED.show();
  }
}





void drawSquare(int topRow, int colStart, CRGB color) {
  for (int row = topRow; row < topRow + 3 && row < HEIGHT; row++) {
    for (int col = colStart; col < colStart + 3 && col < WIDTH; col++) {
      leds[row * WIDTH + col] = color;
    }
  }
}

void Moving_Two_Squares() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time you updated

    static int currentRow1 = 0;
    static int currentRow2 = 0;
    static bool movingDown1 = true;
    static bool movingDown2 = true;

    // Clear all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    // Draw the first square
    drawSquare(currentRow1, 0, Color);

    // Draw the second square
    drawSquare(currentRow2, WIDTH - 3, Color);

    FastLED.show();

    // Move the first square
    if (movingDown1) {
      if (currentRow1 < HEIGHT - 3) {
        currentRow1++;
      } else {
        movingDown1 = false;
      }
    } else {
      if (currentRow1 > 0) {
        currentRow1--;
      } else {
        movingDown1 = true;
      }
    }

    // Move the second square
    if (movingDown2) {
      if (currentRow2 < HEIGHT - 3) {
        currentRow2++;
      } else {
        movingDown2 = false;
      }
    } else {
      if (currentRow2 > 0) {
        currentRow2--;
      } else {
        movingDown2 = true;
      }
    }
  }
}

void drawTriangle(int baseRow, bool pointingUp) {
  // Clear all LEDs
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // Draw the triangle
  if (pointingUp) {
    leds[baseRow * WIDTH + 2] = Color;
    leds[baseRow * WIDTH + 3] = Color;
    leds[baseRow * WIDTH + 4] = Color;
    leds[baseRow * WIDTH + 5] = Color;
    leds[baseRow * WIDTH + 6] = Color;
    
    if (baseRow > 0) {
      leds[(baseRow - 1) * WIDTH + 2] = Color;
      leds[(baseRow - 1) * WIDTH + 3] = Color;
      leds[(baseRow - 1) * WIDTH + 4] = Color;
    }
    
    if (baseRow > 1) {
      leds[(baseRow - 2) * WIDTH + 4] = Color;
    }
  } else {
    leds[baseRow * WIDTH + 4] = Color;
    
    if (baseRow > 0) {
      leds[(baseRow - 1) * WIDTH + 2] = Color;
      leds[(baseRow - 1) * WIDTH + 3] = Color;
      leds[(baseRow - 1) * WIDTH + 4] = Color;
    }
    
    if (baseRow > 1) {
      leds[(baseRow - 2) * WIDTH + 2] = Color;
      leds[(baseRow - 2) * WIDTH + 3] = Color;
      leds[(baseRow - 2) * WIDTH + 4] = Color;
      leds[(baseRow - 2) * WIDTH + 5] = Color;
      leds[(baseRow - 2) * WIDTH + 6] = Color;
    }
  }

  FastLED.show();
}

void Triangle_Bottom_to_Top() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time you updated

    static int currentRow = HEIGHT - 1;
    static bool movingUp = true;

    // Draw the triangle
    drawTriangle(currentRow, movingUp);

    // Move the triangle
    if (movingUp) {
      if (currentRow > 2) {
        currentRow--;
      } else {
        movingUp = false;
      }
    } else {
      if (currentRow < HEIGHT - 1) {
        currentRow++;
      } else {
        movingUp = true;
      }
    }
  }
}

void Moving_Square_3x3() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time you updated

    static int currentRow = 0;
    static bool movingDown = true;

    // Clear all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    // Draw the 3x3 square
    for (int row = currentRow; row < currentRow + 3 && row < HEIGHT; row++) 
    {
      if(row % 2)
      {
        for (int col = 3; col < 6 && col < WIDTH; col++) 
        {
          leds[row * WIDTH + col] = Color;
        }
      }
      else 
      {
        for (int col = 2; col < 5 && col < WIDTH; col++) 
          {
          leds[row * WIDTH + col] = Color;
          }
      }
    }
    FastLED.show();

    // Move the square
    if (movingDown) {
      if (currentRow < HEIGHT - 3) {
        currentRow++;
      } else {
        movingDown = false;
      }
    } else {
      if (currentRow > 0) {
        currentRow--;
      } else {
        movingDown = true;
      }
    }
  }
}
void adc_top_to_bottom_1()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 5) {
    previousMillis = currentMillis;  // Save the last time you updated

 if(ADC_value < 1000)
      {
        
        setRow(counter, Color);
        counter++;
        if (counter == HEIGHT-1)
        {
          counter = 9 ;
        }
      }
      else 
      {
        setRow(counter, CRGB::Black);
        counter--;
        if (counter==0)
        {
          counter = 1 ;
        }
        
         
      }
 
    FastLED.show();
 //ADC_Bottom_to_Top();
  }
}
void adc_bottom_to_top_1()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 10) {
    previousMillis = currentMillis;  // Save the last time you updated
 static signed int counter_1 = HEIGHT-1;
 if(ADC_value < 1000)
      {
        
        
        setRow(counter_1, Color);
        counter_1--;
        if (counter_1 == 0)
        {
          counter_1 = 0 ;
        }
      }
      else 
      {
        setRow(counter_1, CRGB::Black);
        counter_1++;
        if (counter_1==HEIGHT-1)
        {
          counter_1 = 9 ;
        }
        
         
      }
 
    FastLED.show();
 //ADC_Bottom_to_Top();
  }
}
void drawSnake(int snakePositions[][2], CRGB color) {
  for (int i = 0; i < SNAKE_LENGTH; i++) {
    int row = snakePositions[i][0];
    int col = snakePositions[i][1];
    if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
      leds[row * WIDTH + col] = color;
    }
  }
}

void  Double_Snake_Bottom_Left_to_Top_Right() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Save the last time you updated

    static int snake1Row = HEIGHT - 1;
    static int snake1Col = 0;
    static bool snake1MovingRight = true;
    static int snake1Positions[SNAKE_LENGTH][2];
    static int snake1Index = 0;

    static int snake2Row = HEIGHT - 1;
    static int snake2Col = WIDTH - 1;
    static bool snake2MovingLeft = true;
    static int snake2Positions[SNAKE_LENGTH][2];
    static int snake2Index = 0;

    // Clear all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    // Store the current position of the head of the first snake
    snake1Positions[snake1Index][0] = snake1Row;
    snake1Positions[snake1Index][1] = snake1Col;
    snake1Index = (snake1Index + 1) % SNAKE_LENGTH;

    // Store the current position of the head of the second snake
    snake2Positions[snake2Index][0] = snake2Row;
    snake2Positions[snake2Index][1] = snake2Col;
    snake2Index = (snake2Index + 1) % SNAKE_LENGTH;

    // Draw the first snake
    drawSnake(snake1Positions, Color);

    // Draw the second snake
    drawSnake(snake2Positions, Color);

    FastLED.show();

    // Move the first snake
    if (snake1MovingRight) {
      if (snake1Col < WIDTH / 2 - 1) {
        snake1Col++;
      } else {
        snake1Col = WIDTH / 2 - 1;
        snake1Row--;
        snake1MovingRight = false;
      }
    } else {
      if (snake1Col > 0) {
        snake1Col--;
      } else {
        snake1Col = 0;
        snake1Row--;
        snake1MovingRight = true;
      }
    }

    // Move the second snake
    if (snake2MovingLeft) {
      if (snake2Col > WIDTH / 2) {
        snake2Col--;
      } else {
        snake2Col = WIDTH / 2;
        snake2Row--;
        snake2MovingLeft = false;
      }
    } else {
      if (snake2Col < WIDTH - 1) {
        snake2Col++;
      } else {
        snake2Col = WIDTH - 1;
        snake2Row--;
        snake2MovingLeft = true;
      }
    }

    // If the first snake reaches the top row, reset to start from the bottom-left
    if (snake1Row < 0) {
      snake1Row = HEIGHT - 1;
      snake1Col = 0;
      snake1MovingRight = true;
      snake1Index = 0; // Reset the snake index
      fill_solid(leds, NUM_LEDS, CRGB::Black);
    }

    // If the second snake reaches the top row, reset to start from the bottom-right
    if (snake2Row < 0) {
      snake2Row = HEIGHT - 1;
      snake2Col = WIDTH - 1;
      snake2MovingLeft = true;
      snake2Index = 0; // Reset the snake index
      fill_solid(leds, NUM_LEDS, CRGB::Black);
    }
  }
}

void Snake_Game()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Move the snake
    for (int i = SNAKE_LENGTH - 1; i > 0; i--) {
      snake[i] = snake[i - 1];
    }
    snake[0] += direction;

    // Check for boundaries and wrap around
    if (snake[0] >= NUM_LEDS) snake[0] -= NUM_LEDS;
    if (snake[0] < 0) snake[0] += NUM_LEDS;

    // Check for zigzag movement
   
  // Check for zigzag movement
    
if (direction == -1) {
      // Move left
      if (snake[0] % WIDTH == 0) {
        direction = -WIDTH;  // Move up
      }
    } else if (direction == -WIDTH) {
      // Move up
      if (snake[0] < WIDTH) {
        direction = 1;  // Move right
      }
    }

   /* if (direction == -WIDTH && (snake[0] % WIDTH == 0))
     {
      direction = 1;  // Move right
     } 
    else if (direction == 1 && ((snake[0] + 1) % WIDTH == 0)) 
    {
      direction = -WIDTH;  // Move up
    } 
    else if (direction == -WIDTH && (snake[0] % WIDTH == WIDTH - 1))
     {
      direction = 1;  // Move left
    } 
    else if (direction == 1 && (snake[0] % WIDTH == 0)) {
      direction = -WIDTH;  // Move up
    }*/

    // Check if snake eats the target
    if (snake[0] == targetLED) {
      
      targetLED = random(NUM_LEDS);
      snakeColorIndex = (snakeColorIndex + 1) % (sizeof(colors) / sizeof(CRGB));
    }

    // Update the LED matrix
    FastLED.clear();
    leds[targetLED] = CRGB::White;  // Target LED color
    for (int i = 0; i < SNAKE_LENGTH; i++) {
      leds[snake[i]] = colors[snakeColorIndex];  // Snake color
    }
    FastLED.show();
  }
}


void Snake_Bottom_Left_to_Top_Right() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
  static int ledIndex = NUM_LEDS - SNAKE_LENGTH ;
    
    static int snakeIndex = 0;

  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) 
  {
    previousMillis = currentMillis; // Save the last time you updated

    

        fill_solid(leds, NUM_LEDS, CRGB::Black);
        ledIndex--;//= NUM_LEDS - 1 - ((currentMillis / interval) % NUM_LEDS);
        if(ledIndex < 0 ) {ledIndex = NUM_LEDS ;}//- SNAKE_LENGTH;
        for (int i = 0; i < SNAKE_LENGTH; i++)
        leds[ledIndex + i] = Color; // Turn on the current LED


    FastLED.show();

   
  }
}



void Random()
{
  unsigned long currentMillis = millis();
 
    if (currentMillis - previousMillis >= interval) 
    {
       previousMillis = currentMillis;
        for(int i =0 ;i<NUM_LEDS ;i++)
        {
          leds[i]=CHSV(random(255), 255, 255);
        }
        FastLED.show();
    }
}

void One_Dot_Left() {
    static unsigned long previousMillis = 0;
    static int ledIndex=0;
    // Check if the interval has passed
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        // Update the previousMillis for the next iteration
        previousMillis = currentMillis;

        // Turn off all LEDs
        fill_solid(leds, NUM_LEDS, CRGB::Black);

        // Calculate the LED index based on time, counting down
        ledIndex++;//= NUM_LEDS - 1 - ((currentMillis / interval) % NUM_LEDS);
        if(ledIndex > NUM_LEDS-1 ) ledIndex =0;
        leds[ledIndex] = Color; // Turn on the current LED

        FastLED.show();
    }
}

void One_Dot_Right() {
    static unsigned long previousMillis = 0;
    static int ledIndex = NUM_LEDS-1;

    // Check if the interval has passed
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        // Update the previousMillis for the next iteration
        previousMillis = currentMillis;

        // Turn off all LEDs
        fill_solid(leds, NUM_LEDS, CRGB::Black);

        // Calculate the LED index based on time
        ledIndex --; //= (currentMillis / interval) % NUM_LEDS;
        if(ledIndex < 0) ledIndex = NUM_LEDS;
        leds[ledIndex] = Color; // Turn on the current LED

        FastLED.show();
    }
}




void One_Dot_Down() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time you updated

    // Turn off all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    // Turn on the current LED
    leds[currentRow * WIDTH + currentCol] = Color;  // Assuming 'Color' is CRGB::Red
    FastLED.show();

    // Move to the next row
    currentRow++;

    // If we've reached the bottom, move to the next column and reset the row
    if (currentRow >= HEIGHT) {
      currentRow = 0;
      currentCol++;

      // If we've reached the last column, reset to the first column
      if (currentCol >= WIDTH) {
        currentCol = 0;
      }
    }
  }
}

void growShrinkDiagonal_22() {
  static int size = 1; // Current size of the diagonal line
  static bool growing = true;
  static unsigned long previousMillis = 0;

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time the dot moved
    previousMillis = currentMillis;

    // Clear the previous frame
    FastLED.clear();

    // Draw the diagonal shape
    for (int i = 0; i < size; i++) {
      for (int j = 0; j <= i; j++) {
        int row = HEIGHT - 1 - i + j;
        int column = WIDTH - 1 - j;

        if (row >= 0 && row < HEIGHT && column >= 0 && column < WIDTH) {
          int index;
          if (row % 2 == 0) {
            index = row * WIDTH + column;
          } else {
            index = row * WIDTH + (WIDTH - 1 - column);
          }

          leds[index] = Color;
        }
      }
    }

    // Show the updated LEDs
    FastLED.show();

    // Update the size for the next frame
    if (growing) {
      size++;
      if (size > HEIGHT + WIDTH - 1) {
        size = HEIGHT + WIDTH - 1;
        growing = false;
      }
    } else {
      size--;
      if (size < 1) {
        size = 1;
        growing = true;
      }
    }
  }
}




void One_Dot_Up() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time you updated

    // Turn off all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    // Turn on the current LED
    leds[currentRow * WIDTH + currentCol] = Color;  // Assuming 'Color' is CRGB::Red
    FastLED.show();

    // Move to the previous row
    currentRow--;

    // If we've reached the top, move to the next column and reset the row to the bottom
    if (currentRow < 0) {
      currentRow = HEIGHT - 1;
      currentCol++;

      // If we've reached the last column, reset to the first column
      if (currentCol >= WIDTH) {
        currentCol = 0;
      }
    }
  }
}

void Bottom_to_Top() {
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  static unsigned long previousMillis = 0;
  static int currentRow = HEIGHT - 1; // Start from the bottom row

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time you updated

    // Light up the current row in red
    setRow(currentRow, Color);

    // Keep the previous rows lit in red
    for (int prevRow = HEIGHT - 1; prevRow > currentRow; prevRow--) {
      setRow(prevRow, Color);
    }

    FastLED.show();

    // Move to the previous row
    currentRow--;

    // If we've lit all rows, reset to the last row
    if (currentRow < 0) {
      // Clear the matrix after the pattern has been displayed
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      currentRow = HEIGHT - 1;  // Reset to start over
    }
  }
}

void Top_to_Bottom() {
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  static unsigned long previousMillis = 0;
  static int currentRow = 0; // Start from the top row

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time you updated

    // Light up the current row in red
    setRow(currentRow, Color);

    // Keep the previous rows lit in red
    for (int prevRow = 0; prevRow < currentRow; prevRow++) {
      setRow(prevRow, Color);
    }

    FastLED.show();

    // Move to the next row
    currentRow++;

    // If we've lit all rows, reset to the first row
    if (currentRow >= HEIGHT) {
      // Clear the matrix after the pattern has been displayed
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      currentRow = 0;  // Reset to start over
    }
  }
}





void Left_to_Right() {
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time you updated

    // Light up the current column in red
    setColumn(currentCol, Color);

    // Keep the previous columns lit in red
    for (int prevCol = 0; prevCol < currentCol; prevCol++) {
      setColumn(prevCol, Color);
    }

    FastLED.show();

    // Move to the next column
    currentCol++;

    // If we've lit all columns, reset to the first column
    if (currentCol >= WIDTH) {
      // Clear the matrix after the pattern has been displayed
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      currentCol = 0;  // Reset to start over
    }
  }
}
void Right_to_Left() {
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  static unsigned long previousMillis = 0;
  static int currentCol = WIDTH - 1; // Start from the rightmost column

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time you updated

    // Light up the current column in red
    setColumn(currentCol, Color);

    // Keep the previous columns lit in red
    for (int prevCol = WIDTH - 1; prevCol > currentCol; prevCol--) {
      setColumn(prevCol, Color);
    }

    FastLED.show();

    // Move to the previous column
    currentCol--;

    // If we've lit all columns, reset to the last column
    if (currentCol < 0) {
      // Clear the matrix after the pattern has been displayed
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      currentCol = WIDTH - 1;  // Reset to start over
    }
  }
}

void Bottom_to_Top_Single_Row() {
  unsigned long currentMillis = millis();

  // Check if the interval has passed
  static unsigned long previousMillis = 0;
  static int currentRow = HEIGHT - 1; // Start from the bottom row

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time you updated

   
    fill_solid(leds, NUM_LEDS, CRGB::Black);

    // Light up the current row
    setRow(currentRow, Color);

    FastLED.show();

    // Move to the previous row
    currentRow--;

    // If we've lit all rows, reset to the last row
    if (currentRow < 0) {
      currentRow = HEIGHT - 1;  // Reset to start over
    }
  }
}
void Top_to_Bottom_Single_Row() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
 
  
  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time you updated
    
    // Clear all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    
    // Light up the current row
    setRow(currentRow, Color);
    
    FastLED.show();
    
    // Move to the next row
    currentRow++;
    
    // If we've reached the last row, reset to the first row
    if (currentRow >= HEIGHT) {
      currentRow = 0;
    }
  }
}

void Left_to_Right_Single_Colom()
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
 
  
  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time you updated
    
    // Clear all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    
    // Light up the current row
    setColumn(currentCol, Color);
    
    FastLED.show();
    
    // Move to the next row
    currentCol++;
    
    // If we've reached the last row, reset to the first row
    if (currentCol >= WIDTH) {
      currentCol = 0;
    }
  }
}

void Right_to_Left_Single_Colom()
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();
 
  
  // Only update LEDs if enough time has passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Save the last time you updated
    
    // Clear all LEDs
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    
    // Light up the current row
    setColumn(currentCol, Color);
    
    FastLED.show();
    
    // Move to the next row
    currentCol--;
    
    // If we've reached the last row, reset to the first row
    if (currentCol < 0) {
      currentCol = WIDTH-1;
    }
  }
}

/*void setColumn(int column, CRGB color) {
  for (int row = 0; row < HEIGHT; row++) {
    leds[row * WIDTH + column] = color;
  }
}*/
void setColumn(int column, CRGB color) {
  for (int row = 0; row < HEIGHT; row++) {
    int index;
    if (row % 2 == 0) {
      // Even rows (0, 2, 4, ...) go left to right
      index = row * WIDTH + column;
    } else {
      // Odd rows (1, 3, 5, ...) go right to left
      index = row * WIDTH + (WIDTH - 1 - column);
    }
    leds[index] = color;
  }
}




void setRow(int row, CRGB color) {
  for (int col = 0; col < WIDTH; col++) {
    leds[row * WIDTH + col] = color;
  }
}

void setRow_0(int row, CRGB color) {
  if(row >= 0 )
  {
    for (int col = 0; col < WIDTH; col++) {
      leds[row * WIDTH + col] = color;
    }
  }
}


