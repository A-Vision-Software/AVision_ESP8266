/*******************************************************************************
*
* (c) 2021 Copyright A-Vision Software
*
* File description :        Dot-matrix display
*
* Created by       :        Arnold Velzel
* Created on       :        24-09-2021
*
*******************************************************************************/

#include <avision_debug.h>
#include <avision_display.h>

using namespace AVision;

void dotmatrixDisplay::showDot(uint8_t r, uint16_t c)
{
    if (!display->getPoint(r, c))
    {
        display->setPoint(r, c, true);
    }
}
void dotmatrixDisplay::hideDot(uint8_t r, uint16_t c)
{
    if (display->getPoint(r, c))
    {
        display->setPoint(r, c, false);
    }
}
void dotmatrixDisplay::flashDot(uint8_t r, uint16_t c, int timeOn = 100, int timeOff = 900)
{
    static unsigned int last_toggle = 0;
    static bool state = false;
    unsigned int m = millis();
    if (state && (m - last_toggle) > timeOn)
    {
        state = false;
        hideDot(r, c);
        last_toggle = m;
    }
    if (!state && (m - last_toggle) > timeOff)
    {
        state = true;
        showDot(r, c);
        last_toggle = m;
    }
}

void dotmatrixDisplay::setRow(uint8_t row, uint8_t value)
{
    display->setRow(row, value);
}
void dotmatrixDisplay::setColumn(uint8_t column, uint8_t value)
{
    display->setColumn(column, value);
}

void dotmatrixDisplay::showText(uint8_t modStart, uint8_t modEnd, char *pMsg)
// Print the text string to the LED matrix modules specified.
// Message area is padded with blank columns after printing.
{
    char c;
    uint8_t state = 0;
    uint8_t curLen;
    uint16_t showLen;
    uint8_t cBuf[8];
    int16_t col = ((modEnd + 1) * COL_SIZE) - 1;
    bool tiny = false;

    display->control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

    do // finite state machine to print the characters in the space available
    {
        switch (state)
        {
        case 0: // Load the next character from the font table
            // if we reached end of message, reset the message pointer
            c = *pMsg;
            if (c == '\0')
            {
                showLen = col - (modEnd * COL_SIZE); // padding characters
                state = 2;
                break;
            }
            if (c == '▼')
            {
                tiny = true;
                break;
            }
            if (c == '▲')
            {
                tiny = false;
                break;
            }

            if (tiny && c >= 42 && c <= 62)
            {
                c += 100;
            }

            // retrieve the next character form the font file
            showLen = display->getChar(c, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
            pMsg++;
            curLen = 0;
            state++;
            // !! deliberately fall through to next state to start displaying

        case 1: // display the next part of the character
            display->setColumn(col--, cBuf[curLen++]);

            // done with font character, now display the space between chars
            if (curLen == showLen)
            {
                showLen = CHAR_SPACING;
                state = 2;
            }
            break;

        case 2: // initialize state for displaying empty columns
            curLen = 0;
            state++;
            // fall through

        case 3: // display inter-character spacing or end of message padding (blank columns)
            display->setColumn(col--, 0);
            curLen++;
            if (curLen == showLen)
                state = 0;
            break;

        default:
            col = -1; // this definitely ends the do loop
        }
        ESP.wdtFeed();
    } while (col >= (modStart * COL_SIZE));

    // display->transform(modStart, modEnd, MD_MAX72XX::TFUD); display->transform(modStart, modEnd, MD_MAX72XX::TFLR);
    display->control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void dotmatrixDisplay::setIntensity(uint8_t intensity, uint8_t startDev = 0, uint8_t endDev = 7)
{
    static uint8_t currentIntensity = 101;
    if (intensity != currentIntensity || currentIntensity > 100)
    {
        display->control(startDev, endDev, MD_MAX72XX::INTENSITY, intensity * MAX_INTENSITY / 100);
        currentIntensity = intensity;
    }
}
void dotmatrixDisplay::setIntensity(uint8_t intensity)
{
    setIntensity(intensity, 0, 7);
}
void dotmatrixDisplay::shiftLeft()
{
    display->transform(MD_MAX72XX::TSL);
}

void dotmatrixDisplay::invert(uint8_t startDev, uint8_t endDev)
{
    display->transform(startDev, endDev, MD_MAX72XX::TINV);
}
void dotmatrixDisplay::setFont(MD_MAX72XX::fontType_t *f)
{
    display->setFont(f);
}

void dotmatrixDisplay::loop()
{
    size_t newLine = text.indexOf("\n");
    if (newLine >= 0)
    {
        if (newLine > 0)
        {
            showText(display_columns, display_columns * display_rows - 1, (char *)text.substring(0, newLine).c_str());
        }
        showText(0, display_columns - 1, (char *)text.substring(newLine + 1).c_str());
    }
    else
    {
        showText(0, display_columns * display_rows - 1, (char *)text.c_str());
    }
}
void dotmatrixDisplay::init(int columns, int rows, MD_MAX72XX::moduleType_t hardware_type)
{
    display_columns = columns;
    display_rows = rows;

    // SPI hardware interface
    display = new MD_MAX72XX(hardware_type, DATA_PIN, CLK_PIN, CS_PIN, display_columns * display_rows);
    display->begin();
    display->setFont(_font_with_tiny_numbers);

    setIntensity(10, 0, display_columns * display_rows);

    dbgln("Display initialised");
}
void dotmatrixDisplay::init(int columns, int rows)
{
    init(columns, rows, DISPLAY_HARDWARE_TYPE);
}
dotmatrixDisplay::dotmatrixDisplay()
{
    display_columns = 1;
    display_rows = 1;
    display_brightness = 1;
    text = "";
}

dotmatrixDisplay::~dotmatrixDisplay()
{
}