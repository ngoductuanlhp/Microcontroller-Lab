//#include <xc.h>
//#include <pic18f8722.h>
//#define IR_PIN PORTAbits.RA0
//
//unsigned char ir_address = 0;
//unsigned char ir_cmd = 0;
//unsigned long ir_code = 0;
//
//char read_NEC() {
//    unsigned long count = 0;
//    unsigned char i;
//    
//    while(IR_PIN && count < 190) {
//        count++;
//        __delay_us(50);
//    }
//    if(count < 160 || count > 189)
//        return 0;
//    
//    count = 0;
//    while(!IR_PIN && count < 95) {
//        count++;
//        __delay_us(50);
//    }
//    if(count < 80 || count > 94)
//        return 0;
//    
//    count = 0;
//    
//    for(i = 0; i < 32; i++) {
//        while(IR_PIN && count < 13) {
//            count++;
//            __delay_us(50);
//        }
//        if(count < 10 || count > 12)
//            return 0;
//        
//        count = 0;
//        while(!IR_PIN && count < 35) {
//            count++;
//            __delay_us(50);
//        }
//        if(count < 10 || count > 34)
//            return 0;
//        if(count < 15)
//            ir_code &= ~(1ul << i);
//        else ir_code |= (1ul << i);
//    }
//    return 1;
//}
//
//void check_NEC() {
//    if(read_NEC()) {
//        ir_address = ir_code & 0x000F;
//        ir_cmd = (ir_code >> 16) & 0x000F;
//    }
//}