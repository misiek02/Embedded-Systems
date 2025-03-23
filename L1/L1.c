#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"
#include "hardware/clocks.h"
#include "hardware/pll.h"


void measure_freqs(void) {
    uint f_pll_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_SYS_CLKSRC_PRIMARY);
    uint f_pll_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_PLL_USB_CLKSRC_PRIMARY);
    uint f_rosc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_ROSC_CLKSRC);
    uint f_clk_sys = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS);
    uint f_clk_peri = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_PERI);
    uint f_clk_usb = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_USB);
    uint f_clk_adc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_ADC);
#ifdef CLOCKS_FC0_SRC_VALUE_CLK_RTC
    uint f_clk_rtc = frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_RTC);
#endif
 
    printf("pll_sys  = %dkHz\n", f_pll_sys);
    printf("pll_usb  = %dkHz\n", f_pll_usb);
    printf("rosc     = %dkHz\n", f_rosc);
    printf("clk_sys  = %dkHz\n", f_clk_sys);
    printf("clk_peri = %dkHz\n", f_clk_peri);
    printf("clk_usb  = %dkHz\n", f_clk_usb);
    printf("clk_adc  = %dkHz\n", f_clk_adc);
#ifdef CLOCKS_FC0_SRC_VALUE_CLK_RTC
    printf("clk_rtc  = %dkHz\n", f_clk_rtc);
#endif
 
    // Can't measure clk_ref / xosc as it is the ref
}

void choice0(){
    clock_configure(clk_ref,CLOCKS_CLK_REF_CTRL_SRC_VALUE_XOSC_CLKSRC, 0, 12*MHZ, 12*MHZ);
    clock_configure(clk_peri, 0, CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS, 12*MHZ, 12*MHZ);
    stdio_init_all();
}

// void choice0(){
//     clock_configure(clk_sys, 0, CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLK_REF, 12*MHZ, 12*MHZ);
//     pll_deinit(pll_sys);
// }

void choice1(){
    pll_init(pll_sys, 1, 1500*MHZ, 5, 3);
    clock_configure(clk_sys, CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX, CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, 12*MHZ, 100*MHZ);
}

// void choice2(){
//     pll_init(pll_sys);
//     clock_configure(clk_sys, CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX, CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, 12*MHZ, 50*MHZ);
// }

// void choice3(){
//     pll_init(pll_sys);
//     clock_configure(clk_sys, CLOCKS_CLK_SYS_CTRL_SRC_VALUE_CLKSRC_CLK_SYS_AUX, CLOCKS_CLK_SYS_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS, 12*MHZ, 25*MHZ);
// }

int main()
{
    stdio_init_all();
    int choice = -1;
    measure_freqs();

    while (true) {
        printf("Enter a number 0..4: \n");
        choice = -1;
        fflush(stdin);
        scanf("%d", &choice);
        printf("U chose: %d\n", choice);

        switch (choice)
        {
        case 0:
            printf("Case %d\n", choice);
            choice0();
            measure_freqs();
            break;
        case 1:
            printf("Case %d\n", choice);
            choice1();
            measure_freqs();
            break;
        case 2:
            printf("Case %d\n", choice);
            break;
        case 3:
            printf("Case %d\n", choice);
            break;        
        default:
            printf("Wrong option!!!\n");
            break;
        }

        printf("Hello, world!\n");
        sleep_ms(1000);

    }
}
