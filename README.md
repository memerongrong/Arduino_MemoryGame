# Arduino_MemoryGame

This is my first Arduino project, **Memory Game**

There are three points.
1. Improve the code's readability by using **constants**
   
```c++
const int melody[] = {261, 440, 698, 493, 987, 622, 740};
//C4: 0, A4: 1, F5: 2, 4B: 3, 5B: 4, 5D#: 5, 5F#: 6 

const int BLUE_LIGHT[3] = {2, 3, 4};
const int BLUE_BUTTON[3] = {5, 6, 7};
const int LED_RED = 9;
const int LED_BLUE = 10;
const int LED_GREEN = 11;
const int START_BUTTON = 12;
const int BUZZER = 13;

void setup()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BLUE_LIGHT[0], OUTPUT);
  pinMode(BLUE_LIGHT[1], OUTPUT);
  pinMode(BLUE_LIGHT[2], OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BLUE_BUTTON[0], INPUT);
  pinMode(BLUE_BUTTON[1], INPUT);
  pinMode(BLUE_BUTTON[2], INPUT);
  pinMode(START_BUTTON, INPUT);
  Serial.begin(9600);
}
```

2. Increase the fun of the game by using **random functions**
```c++
void Level(int inputLevel)
{
  for (int i = 0; i < level; i++)
  {
    int randomLight = random(0, 3);
    LightOn(randomLight);
    QUIZ[i] = randomLight;
    Serial.print(randomLight);
    Serial.println(" is on!");
    Serial.print("Quiz's ");
    Serial.print(i);
    Serial.print(" member is ");
    Serial.println(QUIZ[i]);
  }
}
```

3. Track the current state and implement the game logic by using boolean variables
```c++
void loop()
{  
  delay(100);

  if (!isStarted && !canInput)
  {
    BeforeStart();
  }
  
  if (digitalRead(START_BUTTON) == HIGH)
  {
    Serial.println("Start Button pushed!");
  	GameStart();
  }

  // ... (중략) ...

  //게임 진행
  if (canInput && nowInput < level)
  {
    InputButton();
  }
  
  //채점 진행
  if (canInput && nowInput == level)
  {
    Grade();
  }
  
  //10단계 달성 시 게임 종료
  if (isStarted == true || level > maxLevel)
  {
    PlayerWin();
  }
}
```

You can see the demo video at
