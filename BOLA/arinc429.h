#ifndef ARINC429_H
#define ARINC429_H

#include <cstdint>
#include "enum.h"

class Arinc429
{

    struct Arinc429Fields {
        Arinc429Label label : 8; // Биты 1-8: Идентификатор/Label
        Arinc429SDI sdi     : 2; // Биты 9-10: SDI
        uint32_t data       : 19; // Биты 11-29: Данные        max = 2^19 (524288)
        Arinc429SSM ssm     : 2; // Биты 30-31: SSM/Матрица
        int p               : 1; // Бит 32: Бит четности/Parity
    };

    union Arinc429Word {
        uint32_t word;          // Доступ ко всему слову как к 32-битному целому
        Arinc429Fields fields;  // Доступ к полям через структуру
        Arinc429type type;
    };

    int count_set_bits(uint32_t n) {
        int count = 0;
        while (n > 0) {
            n &= (n - 1);
            count++;
        }
        return count;
    }

public:
    Arinc429();
    Arinc429Word encodeWord(Arinc429type _type,
                            Arinc429Label _label, Arinc429SDI _sdi,
                            uint32_t _data, Arinc429SSM _ssm){
        Arinc429Word word;
        word.type = _type;
        word.fields.label = _label;
        word.fields.sdi = _sdi;
        word.fields.ssm = _ssm;
        word.fields.data = _data;
        if (count_set_bits(word.word) % 2 == 0){
            word.word |= 0x80000000;
        }else{
            word.word &= 0x7FFFFFFF;
        }
        return word;
    }
};

#endif // ARINC429_H
