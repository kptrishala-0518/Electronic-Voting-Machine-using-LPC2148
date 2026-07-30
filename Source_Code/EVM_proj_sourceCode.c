#include <lpc214x.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

// LCD pins
#define LCD_RS 0x00000010        // P0.4
#define LCD_RW 0x00000020        // P0.5
#define LCD_EN 0x00000040        // P0.6
#define LCD_DATA_MASK 0x0000F000 // P0.12 - P0.15

// Keypad pins
#define ROW_MASK ((1 << 19) | (1 << 20) | (1 << 21) | (1 << 22)) // P1.19–22
#define COL_MASK ((1 << 16) | (1 << 17) | (1 << 18))             // P1.16–18

// Voting button (End button at P0.20)
#define END_BUTTON_MASK (1 << 20)

void delay(unsigned int count)
{
    unsigned int j, k;
    for (j = 0; j <= count; j++)
        for (k = 0; k <= 600; k++)
            ;
}

// LCD functions
void LCD_CMD(char cmd)
{
    IO0PIN = (IO0PIN & ~LCD_DATA_MASK) | ((cmd & 0xF0) << 8);
    IO0CLR = LCD_RS | LCD_RW;
    IO0SET = LCD_EN;
    delay(2);
    IO0CLR = LCD_EN;

    IO0PIN = (IO0PIN & ~LCD_DATA_MASK) | ((cmd & 0x0F) << 12);
    IO0CLR = LCD_RS | LCD_RW;
    IO0SET = LCD_EN;
    delay(2);
    IO0CLR = LCD_EN;
}

void LCD_INIT()
{
    IO0DIR |= LCD_RS | LCD_RW | LCD_EN | LCD_DATA_MASK;
    delay(50);

    LCD_CMD(0x02);
    LCD_CMD(0x28);
    LCD_CMD(0x0C);
    LCD_CMD(0x06);
    LCD_CMD(0x01);

    delay(2);
}

void LCD_CHAR(char data)
{
    IO0PIN = (IO0PIN & ~LCD_DATA_MASK) | ((data & 0xF0) << 8);
    IO0SET = LCD_RS;
    IO0CLR = LCD_RW;
    IO0SET = LCD_EN;
    delay(2);
    IO0CLR = LCD_EN;

    IO0PIN = (IO0PIN & ~LCD_DATA_MASK) | ((data & 0x0F) << 12);
    IO0SET = LCD_RS;
    IO0CLR = LCD_RW;
    IO0SET = LCD_EN;
    delay(2);
    IO0CLR = LCD_EN;
}

void LCD_STRING(char *msg)
{
    while (*msg)
    {
        LCD_CHAR(*msg++);
    }
}

// Keypad
char keypad[4][3] =
    {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}};

void keypad_init()
{
    PINSEL2 = 0x00000000;
    IO1DIR |= ROW_MASK;
    IO1DIR &= ~COL_MASK;
    IO1SET = ROW_MASK;
}

char get_key()
{
    int row, col;

    for (row = 0; row < 4; row++)
    {
        IO1SET = ROW_MASK;
        IO1CLR = (1 << (19 + row));
        delay(2);

        for (col = 0; col < 3; col++)
        {
            if (!(IO1PIN & (1 << (16 + col))))
            {
                delay(20);
                while (!(IO1PIN & (1 << (16 + col))))
                    ;
                return keypad[row][col];
            }
        }
    }

    return 0;
}

int main()
{
    char passwords[10][5] =
        {
            "1234", "2345", "3456", "4567", "5678",
            "6789", "7890", "8901", "9012", "0123"};

    char input[5];
    int i, attempts;
    int candidate_count = 0;
    int candidate_id = 0;
    char key;

    int vote_p1 = 0;
    int vote_p2 = 0;
    int vote_p3 = 0;
    int vote_nota = 0;

    char line1[32];

    IO0DIR |= (1 << 4) | (1 << 5) | (1 << 6) | LCD_DATA_MASK;
    IO0DIR &= ~((1 << 16) | (1 << 17) | (1 << 18) | (1 << 19)); // Voting buttons
    IO1DIR |= (1 << 28) | (1 << 29) | (1 << 30) | (1 << 31);    // LEDs

    LCD_INIT();
    keypad_init();

    LCD_CMD(0x01);
    LCD_CMD(0x80);
    LCD_STRING(" Welcome to the");
    LCD_CMD(0xC0);
    LCD_STRING(" Voting System");
    delay(10000);

    LCD_CMD(0x01);
    LCD_CMD(0x80);
    LCD_STRING(" Voting Started");
    delay(10000);

    while (candidate_count < 10)
    {
        int access_granted = 0;

        candidate_id++;

        LCD_CMD(0x01);
        LCD_CMD(0x80);
        sprintf(line1, " Candidate %d", candidate_id);
        LCD_STRING(line1);
        delay(15000);

        LCD_CMD(0x01);
        LCD_CMD(0x80);
        sprintf(line1, " Enter Pass %d:", candidate_id);
        LCD_STRING(line1);
        LCD_CMD(0xC0);

        attempts = 0;

        while (attempts < 3)
        {
            i = 0;
            memset(input, 0, sizeof(input));

            while (1)
            {
                key = get_key();

                if (key)
                {
                    if (key == '#')
                    {
                        input[i] = '\0';
                        break;
                    }
                    else if (i < 4)
                    {
                        input[i++] = key;
                        LCD_CHAR('*');
                    }
                }
            }

            if (strcmp(input, passwords[candidate_count]) == 0)
            {
                access_granted = 1;

                LCD_CMD(0x01);
                LCD_CMD(0x80);
                LCD_STRING(" Access Granted");
                delay(15000);

                break;
            }
            else
            {
                attempts++;

                LCD_CMD(0x01);
                LCD_CMD(0x80);
                LCD_STRING(" Wrong Password");
                delay(15000);

                if (attempts >= 3)
                {
                    LCD_CMD(0x01);
                    LCD_CMD(0x80);
                    LCD_STRING(" Access Denied");
                    delay(15000);

                    LCD_CMD(0x01);
                    LCD_STRING(" Locked");
                    delay(15000);
                }
                else
                {
                    LCD_CMD(0x01);
                    LCD_CMD(0x80);
                    LCD_STRING(" Try Again:");
                    LCD_CMD(0xC0);
                }
            }
        }

        if (!access_granted)
        {
            candidate_count++;
            continue;
        }

        LCD_CMD(0x01);
        LCD_CMD(0x80);
        LCD_STRING(" Press button to");
        LCD_CMD(0xC0);
        LCD_STRING(" cast your vote");
        delay(15000);

        while (1)
        {
            if (IO0PIN & (1 << 16))
            {
                vote_p1++;
                IO1SET = (1 << 28);

                LCD_CMD(0x01);
                LCD_STRING(" Vote casted");
                delay(15000);

                IO1CLR = (1 << 28);
                break;
            }
            else if (IO0PIN & (1 << 17))
            {
                vote_p2++;
                IO1SET = (1 << 29);

                LCD_CMD(0x01);
                LCD_STRING(" Vote casted");
                delay(15000);

                IO1CLR = (1 << 29);
                break;
            }
            else if (IO0PIN & (1 << 18))
            {
                vote_p3++;
                IO1SET = (1 << 30);

                LCD_CMD(0x01);
                LCD_STRING(" Vote casted");
                delay(15000);

                IO1CLR = (1 << 30);
                break;
            }
            else if (IO0PIN & (1 << 19))
            {
                vote_nota++;
                IO1SET = (1 << 31);

                LCD_CMD(0x01);
                LCD_STRING(" Vote casted");
                delay(15000);

                IO1CLR = (1 << 31);
                break;
            }
            else if (IO0PIN & END_BUTTON_MASK)
            {
                LCD_CMD(0x01);
                LCD_CMD(0x80);
                LCD_STRING(" Voting Ended");
                delay(15000);

                goto show_results;
            }
        }

        candidate_count++;
    }

show_results:

    LCD_CMD(0x01);
    LCD_CMD(0x80);
    LCD_STRING(" Voting Time Over");
    LCD_CMD(0xC0);
    LCD_STRING(" Showing Results");
    delay(10000);

    LCD_CMD(0x01);
    LCD_CMD(0x80);
    sprintf(line1, " Party1:%d ", vote_p1);
    LCD_STRING(line1);
    delay(10000);

    LCD_CMD(0x01);
    LCD_CMD(0x80);
    sprintf(line1, " Party2:%d ", vote_p2);
    LCD_STRING(line1);
    delay(10000);

    LCD_CMD(0x01);
    LCD_CMD(0x80);
    sprintf(line1, " Party3:%d ", vote_p3);
    LCD_STRING(line1);
    delay(10000);

    LCD_CMD(0x01);
    LCD_CMD(0x80);
    sprintf(line1, " NOTA:%d ", vote_nota);
    LCD_STRING(line1);
    delay(10000);

    LCD_CMD(0x01);
    LCD_CMD(0x80);

    if (vote_p1 > vote_p2 && vote_p1 > vote_p3 && vote_p1 > vote_nota)
        LCD_STRING(" Winner: Party 1");
    else if (vote_p2 > vote_p1 && vote_p2 > vote_p3 && vote_p2 > vote_nota)
        LCD_STRING(" Winner: Party 2");
    else if (vote_p3 > vote_p1 && vote_p3 > vote_p2 && vote_p3 > vote_nota)
        LCD_STRING(" Winner: Party 3");
    else if (vote_nota > vote_p1 && vote_nota > vote_p2 && vote_nota > vote_p3)
        LCD_STRING(" NOTA Majority");
    else
        LCD_STRING(" No Clear Winner");

    delay(10000);

    LCD_CMD(0x01);
    LCD_STRING(" Thank You!");

    while (1)
        ;
}