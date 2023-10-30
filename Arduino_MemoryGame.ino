const int melody[] = {261, 440, 698, 493, 987, 622, 740};
//C4: 0, A4: 1, F5: 2, 4B: 3, 5B: 4, 5D#: 5, 5F#: 6 

const int BLUE_LIGHT[3] = {2, 3, 4};
const int BLUE_BUTTON[3] = {5, 6, 7};
const int LED_RED = 9;
const int LED_BLUE = 10;
const int LED_GREEN = 11;
const int START_BUTTON = 12;
const int BUZZER = 13;
int countOfButtons = sizeof(BLUE_BUTTON) / sizeof(BLUE_BUTTON[0]);

const int maxLevel = 10;
int level = 0;
int nowInput = 0;

int QUIZ[maxLevel] = {};
int ANSWER[maxLevel] = {};

bool isStarted = false;
bool canInput = false;

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

  //문제를 기출하는 Level 함수를 호출하는 구문
  //함수 호출이 반복되지 않도록 불리언 변수 사용
  if (isStarted && level < maxLevel)
  {
    level++;
    Serial.print("Now your level is ");
    Serial.println(level);
    Level(level);
    isStarted = false;
    canInput = true;
  }
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
  if (isStarted == true && level > maxLevel)
  {
    PlayerWin();
  }
}

//게임 시작 전 상태일 때 호출되는 함수
void BeforeStart()
{
  //Serial.print("Do you want to start? ");
  int r = random(0, 256);
  int b = random(0, 256);
  int g = random(0, 256);
    
  analogWrite(LED_RED, r);
  analogWrite(LED_BLUE, b);
  analogWrite(LED_GREEN, g);
}

//게임 시작 상태로 전환하는 함수
void GameStart()
{
  analogWrite(LED_RED, 0);
  analogWrite(LED_BLUE, 0);
  analogWrite(LED_GREEN, 0);
  
  Serial.println("Game Start!!");

  isStarted = true;
  nowInput = 0;
  tone(BUZZER, melody[3], 100); delay(500);
  tone(BUZZER, melody[3], 100); delay(500);
  tone(BUZZER, melody[3], 100); delay(500);
  tone(BUZZER, melody[4], 500); delay(1000);
}

// 버튼 입력에 따라 전구에 불을 켜는 함수
void LightOn(int buttonNumber)
{
  tone(BUZZER, melody[buttonNumber], 500);
  digitalWrite(BLUE_LIGHT[buttonNumber], HIGH);
  delay(700);
  digitalWrite(BLUE_LIGHT[buttonNumber], LOW);
  delay(300);
}

//랜덤 문제를 기출해주는 함수
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

//버튼 입력을 받고 ANSWER 배열에 저장하는 함수
void InputButton()
{
  for (int buttonNumber = 0; 
       buttonNumber < countOfButtons;
       buttonNumber++)
  {
    if (digitalRead(BLUE_BUTTON[buttonNumber]) == HIGH)
    {
      LightOn(buttonNumber);
      Serial.println(buttonNumber);
      ANSWER[nowInput] = buttonNumber;
      Serial.print(nowInput);
      Serial.print("'s Input key saved: ");
      Serial.println(ANSWER[nowInput]);
      nowInput++;
    } 
  }
}

//플레이어의 입력을 채점하는 함수
void Grade() {
  bool allCorrect = true; // 모든 값이 일치하는지 여부를 추적하는 변수
  canInput = false;
  
  for (int i = 0; i < level; i++) 
  {
    if (QUIZ[i] != ANSWER[i]) 
    {
      allCorrect = false;
      break; // 하나라도 다르면 루프 종료
    }
  }
  //오답이면 삐빅 출력 후 Level 초기화
  if (!allCorrect) 
  {
    Serial.print("Level: ");
    Serial.print(level);
    Serial.println(", FAIL");
    digitalWrite(LED_RED, HIGH);
    tone(BUZZER, melody[0], 100); delay(200);
    tone(BUZZER, melody[0], 300); delay(700);
    digitalWrite(LED_RED, LOW);
    isStarted = false;
    level = 0;
  } 
  //마지막 인덱스까지 정답이면 딩동댕 출력
    else
    {
      Serial.print("Level: ");
      Serial.print(level);
      Serial.println(", PASS");
      digitalWrite(LED_BLUE, HIGH);
      tone(BUZZER, melody[3], 200); delay(300);
      tone(BUZZER, melody[5], 200); delay(300);
      tone(BUZZER, melody[6], 300); delay(500);
      digitalWrite(LED_BLUE, LOW);
      nowInput = 0;
      isStarted = false;
    }
}

//플레이어의 승리를 축하하는 함수
void PlayerWin()
{
  Serial.println("You win!!");
}