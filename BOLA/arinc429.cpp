#include "arinc429.h"

Arinc429::Arinc429()
{

}

Arinc429::Arinc429Word Arinc429::encodeWord(Arinc429type _type,
    Arinc429Label _label, Arinc429SDI _sdi,
    uint32_t _data, Arinc429SSM _ssm) {
    Arinc429Word word;
    word.type = _type;
    word.fields.label = _label;
    word.fields.sdi = _sdi;
    word.fields.ssm = _ssm;
    word.fields.data = _data;
    if (count_set_bits(word.word) % 2 == 0) {
        word.word |= 0x80000000;
    }
    else {
        word.word &= 0x7FFFFFFF;
    }
    return word;
}