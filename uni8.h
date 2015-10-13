

/*
 *
 * uni8
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : uni8.h
 * Date                : 14.09.2015
 * Font size in bytes  : 7854
 * Font width          : 10
 * Font height         : 8
 * Font first char     : 32
 * Font last char      : 256
 * Font used chars     : 224
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>  

const unsigned char uni8[]   = {
    0x1E, 0xAE, // size
    0x02, // width
    0x08, // height
    0x20, // first char
    0xE0, // char count
    
    // char widths
    0x00, 0x01, 0x03, 0x05, 0x05, 0x05, 0x06, 0x01, 0x02, 0x02, 
    0x05, 0x05, 0x02, 0x04, 0x01, 0x05, 0x05, 0x02, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x04, 0x05, 0x05, 0x01, 0x02, 0x03, 0x05, 
    0x03, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x01, 0x04, 0x05, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x07, 0x05, 0x05, 0x05, 0x02, 
    0x05, 0x02, 0x03, 0x05, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 
    0x02, 0x04, 0x04, 0x01, 0x02, 0x04, 0x01, 0x07, 0x04, 0x04, 
    0x04, 0x04, 0x03, 0x04, 0x03, 0x04, 0x04, 0x07, 0x04, 0x04, 
    0x04, 0x03, 0x01, 0x03, 0x04, 0x04, 0x07, 0x04, 0x01, 0x04, 
    0x03, 0x05, 0x03, 0x03, 0x06, 0x05, 0x08, 0x02, 0x09, 0x05, 
    0x06, 0x05, 0x05, 0x01, 0x01, 0x03, 0x03, 0x01, 0x03, 0x04, 
    0x04, 0x08, 0x07, 0x02, 0x07, 0x04, 0x05, 0x05, 0x00, 0x05, 
    0x04, 0x04, 0x06, 0x04, 0x01, 0x03, 0x05, 0x05, 0x05, 0x05, 
    0x05, 0x04, 0x05, 0x02, 0x03, 0x05, 0x01, 0x01, 0x04, 0x05, 
    0x05, 0x01, 0x04, 0x04, 0x04, 0x05, 0x01, 0x05, 0x04, 0x02, 
    0x05, 0x05, 0x05, 0x04, 0x06, 0x05, 0x07, 0x05, 0x05, 0x05, 
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 
    0x07, 0x05, 0x06, 0x05, 0x07, 0x08, 0x07, 0x07, 0x05, 0x05, 
    0x07, 0x05, 0x04, 0x04, 0x04, 0x04, 0x06, 0x04, 0x05, 0x04, 
    0x04, 0x04, 0x04, 0x04, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 
    0x05, 0x04, 0x05, 0x04, 0x05, 0x04, 0x05, 0x06, 0x05, 0x06, 
    0x04, 0x04, 0x05, 0x04, 
    
    // font data
    0x5C, // 33
    0x0C, 0x00, 0x0C, // 34
    0x28, 0x7C, 0x28, 0x7C, 0x28, // 35
    0x48, 0x54, 0xD6, 0x54, 0x24, // 36
    0x44, 0x20, 0x10, 0x08, 0x44, // 37
    0x28, 0x54, 0x54, 0x54, 0x48, 0x20, // 38
    0x0C, // 39
    0x7C, 0x82, // 40
    0x82, 0x7C, // 41
    0x10, 0x54, 0x38, 0x54, 0x10, // 42
    0x10, 0x10, 0x7C, 0x10, 0x10, // 43
    0x00, 0xC0, // 44
    0x10, 0x10, 0x10, 0x10, // 45
    0x40, // 46
    0x40, 0x20, 0x10, 0x08, 0x04, // 47
    0x38, 0x44, 0x44, 0x44, 0x38, // 48
    0x04, 0x7C, // 49
    0x64, 0x54, 0x54, 0x54, 0x58, // 50
    0x44, 0x54, 0x54, 0x54, 0x28, // 51
    0x1C, 0x10, 0x10, 0x10, 0x7C, // 52
    0x5C, 0x54, 0x54, 0x54, 0x24, // 53
    0x38, 0x54, 0x54, 0x54, 0x20, // 54
    0x04, 0x04, 0x64, 0x1C, // 55
    0x28, 0x54, 0x54, 0x54, 0x28, // 56
    0x08, 0x54, 0x54, 0x54, 0x38, // 57
    0x28, // 58
    0x00, 0xC8, // 59
    0x10, 0x28, 0x44, // 60
    0x28, 0x28, 0x28, 0x28, 0x28, // 61
    0x44, 0x28, 0x10, // 62
    0x04, 0x54, 0x14, 0x08, // 63
    0x38, 0x44, 0x54, 0x54, 0x18, // 64
    0x78, 0x14, 0x14, 0x14, 0x78, // 65
    0x7C, 0x54, 0x54, 0x54, 0x28, // 66
    0x38, 0x44, 0x44, 0x44, 0x28, // 67
    0x7C, 0x44, 0x44, 0x44, 0x38, // 68
    0x7C, 0x54, 0x54, 0x54, 0x44, // 69
    0x7C, 0x14, 0x14, 0x14, 0x04, // 70
    0x38, 0x44, 0x54, 0x54, 0x74, // 71
    0x7C, 0x10, 0x10, 0x10, 0x7C, // 72
    0x7C, // 73
    0x20, 0x40, 0x40, 0x3C, // 74
    0x7C, 0x10, 0x10, 0x28, 0x44, // 75
    0x7C, 0x40, 0x40, 0x40, // 76
    0x7C, 0x08, 0x10, 0x08, 0x7C, // 77
    0x7C, 0x08, 0x10, 0x20, 0x7C, // 78
    0x38, 0x44, 0x44, 0x44, 0x38, // 79
    0x7C, 0x14, 0x14, 0x14, 0x08, // 80
    0x38, 0x44, 0x44, 0x44, 0xB8, // 81
    0x7C, 0x14, 0x14, 0x34, 0x48, // 82
    0x48, 0x54, 0x54, 0x54, 0x24, // 83
    0x04, 0x04, 0x7C, 0x04, 0x04, // 84
    0x3C, 0x40, 0x40, 0x40, 0x3C, // 85
    0x1C, 0x20, 0x40, 0x20, 0x1C, // 86
    0x3C, 0x40, 0x40, 0x3C, 0x40, 0x40, 0x3C, // 87
    0x44, 0x28, 0x10, 0x28, 0x44, // 88
    0x04, 0x08, 0x70, 0x08, 0x04, // 89
    0x44, 0x64, 0x54, 0x4C, 0x44, // 90
    0xFE, 0x82, // 91
    0x04, 0x08, 0x10, 0x20, 0x40, // 92
    0x82, 0xFE, // 93
    0x08, 0x04, 0x08, // 94
    0x80, 0x80, 0x80, 0x80, 0x80, // 95
    0x04, 0x08, // 96
    0x30, 0x48, 0x48, 0x70, // 97
    0x7C, 0x48, 0x48, 0x30, // 98
    0x30, 0x48, 0x48, 0x48, // 99
    0x30, 0x48, 0x48, 0x7C, // 100
    0x30, 0x48, 0x68, 0x58, // 101
    0x78, 0x14, // 102
    0x30, 0x48, 0x48, 0xF0, // 103
    0x7C, 0x08, 0x08, 0x70, // 104
    0x74, // 105
    0x00, 0xF4, // 106
    0x7C, 0x20, 0x10, 0x68, // 107
    0x7C, // 108
    0x78, 0x08, 0x08, 0x70, 0x08, 0x08, 0x70, // 109
    0x78, 0x08, 0x08, 0x70, // 110
    0x30, 0x48, 0x48, 0x30, // 111
    0xF8, 0x48, 0x48, 0x30, // 112
    0x30, 0x48, 0x48, 0xF8, // 113
    0x78, 0x10, 0x08, // 114
    0x50, 0x58, 0x68, 0x28, // 115
    0x08, 0x7C, 0x08, // 116
    0x38, 0x40, 0x40, 0x78, // 117
    0x38, 0x40, 0x40, 0x38, // 118
    0x38, 0x40, 0x40, 0x38, 0x40, 0x40, 0x38, // 119
    0x48, 0x30, 0x30, 0x48, // 120
    0x38, 0x40, 0x40, 0xF8, // 121
    0x48, 0x68, 0x58, 0x48, // 122
    0x10, 0x6C, 0x82, // 123
    0xFE, // 124
    0x82, 0x6C, 0x10, // 125
    0x10, 0x08, 0x10, 0x08, // 126
    0x7F, 0x41, 0x41, 0x7F, // 127
    0x04, 0x04, 0x7C, 0x14, 0x14, 0x90, 0x60, // 128
    0x7C, 0x05, 0x04, 0x04, // 129
    0xC0, // 130
    0x78, 0x0A, 0x09, 0x08, // 131
    0xC0, 0x00, 0xC0, // 132
    0x40, 0x00, 0x40, 0x00, 0x40, // 133
    0x10, 0x78, 0x10, // 134
    0x28, 0xFE, 0x28, // 135
    0x10, 0x38, 0x54, 0x54, 0x44, 0x28, // 136
    0x44, 0x20, 0x50, 0x08, 0x44, // 137
    0x40, 0x3C, 0x04, 0x7C, 0x50, 0x50, 0x50, 0x20, // 138
    0x10, 0x28, // 139
    0x7C, 0x10, 0x10, 0x10, 0x7C, 0x50, 0x50, 0x50, 0x20, // 140
    0x7C, 0x10, 0x12, 0x29, 0x44, // 141
    0x04, 0x04, 0x7C, 0x14, 0x14, 0x60, // 142
    0x7C, 0x40, 0xC0, 0x40, 0x7C, // 143
    0x04, 0x7C, 0x14, 0x94, 0x60, // 144
    0x0C, // 145
    0x0C, // 146
    0x0C, 0x00, 0x0C, // 147
    0x0C, 0x00, 0x0C, // 148
    0x10, // 149
    0x10, 0x10, 0x10, // 150
    0x10, 0x10, 0x10, 0x10, // 151
    0x7F, 0x41, 0x41, 0x7F, // 152
    0x04, 0x1C, 0x04, 0x18, 0x04, 0x18, 0x04, 0x18, // 153
    0x40, 0x38, 0x08, 0x78, 0x50, 0x50, 0x20, // 154
    0x28, 0x10, // 155
    0x78, 0x10, 0x10, 0x78, 0x50, 0x50, 0x20, // 156
    0x7C, 0x20, 0x12, 0x69, // 157
    0x04, 0x7C, 0x14, 0x14, 0x60, // 158
    0x78, 0x40, 0xC0, 0x40, 0x78, // 159
    0x4C, 0x51, 0x22, 0x11, 0x0C, // 161
    0x99, 0xA2, 0x62, 0x39, // 162
    0x20, 0x40, 0x40, 0x3C, // 163
    0x10, 0x38, 0x54, 0x54, 0x44, 0x28, // 164
    0x7F, 0x41, 0x41, 0x7F, // 165
    0x6C, // 166
    0x14, 0xAA, 0x50, // 167
    0x7C, 0x55, 0x54, 0x55, 0x44, // 168
    0x38, 0x44, 0x54, 0x54, 0x38, // 169
    0x38, 0x54, 0x54, 0x44, 0x28, // 170
    0x10, 0x28, 0x00, 0x10, 0x28, // 171
    0x10, 0x10, 0x10, 0x10, 0x70, // 172
    0x10, 0x10, 0x10, 0x10, // 173
    0x38, 0x44, 0x74, 0x74, 0x38, // 174
    0x7C, 0x01, // 175
    0x08, 0x14, 0x08, // 176
    0x90, 0x90, 0xFC, 0x90, 0x90, // 177
    0x7C, // 178
    0x74, // 179
    0x7F, 0x41, 0x41, 0x7F, // 180
    0xF8, 0x40, 0x40, 0x38, 0x40, // 181
    0x08, 0x14, 0x7C, 0x14, 0x7C, // 182
    0x10, // 183
    0x32, 0x48, 0x68, 0x5A, // 184
    0x7F, 0x41, 0x41, 0x7F, // 185
    0x38, 0x54, 0x44, 0x28, // 186
    0x28, 0x10, 0x00, 0x28, 0x10, // 187
    0x74, // 188
    0x48, 0x54, 0x54, 0x54, 0x24, // 189
    0x50, 0x58, 0x68, 0x28, // 190
    0x70, 0x04, // 191
    0x78, 0x14, 0x14, 0x14, 0x78, // 192
    0x7C, 0x54, 0x54, 0x54, 0x20, // 193
    0x7C, 0x54, 0x54, 0x54, 0x28, // 194
    0x7C, 0x04, 0x04, 0x04, // 195
    0x80, 0x78, 0x44, 0x44, 0x7C, 0x80, // 196
    0x7C, 0x54, 0x54, 0x54, 0x44, // 197
    0x44, 0x28, 0x10, 0x7C, 0x10, 0x28, 0x44, // 198
    0x28, 0x44, 0x54, 0x54, 0x28, // 199
    0x7C, 0x20, 0x10, 0x08, 0x7C, // 200
    0x7C, 0x21, 0x12, 0x09, 0x7C, // 201
    0x7C, 0x10, 0x10, 0x28, 0x44, // 202
    0x40, 0x3C, 0x04, 0x04, 0x7C, // 203
    0x7C, 0x08, 0x10, 0x08, 0x7C, // 204
    0x7C, 0x10, 0x10, 0x10, 0x7C, // 205
    0x38, 0x44, 0x44, 0x44, 0x38, // 206
    0x7C, 0x04, 0x04, 0x04, 0x7C, // 207
    0x7C, 0x14, 0x14, 0x14, 0x08, // 208
    0x38, 0x44, 0x44, 0x44, 0x44, // 209
    0x04, 0x04, 0x7C, 0x04, 0x04, // 210
    0x4C, 0x50, 0x20, 0x10, 0x0C, // 211
    0x10, 0x28, 0x44, 0xFE, 0x44, 0x28, 0x10, // 212
    0x44, 0x28, 0x10, 0x28, 0x44, // 213
    0x7C, 0x40, 0x40, 0x40, 0x7C, 0x80, // 214
    0x0C, 0x10, 0x10, 0x10, 0x7C, // 215
    0x7C, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x7C, // 216
    0x7C, 0x40, 0x40, 0x7C, 0x40, 0x40, 0x7C, 0x80, // 217
    0x04, 0x04, 0x7C, 0x50, 0x50, 0x50, 0x20, // 218
    0x7C, 0x50, 0x50, 0x50, 0x20, 0x00, 0x7C, // 219
    0x7C, 0x50, 0x50, 0x50, 0x20, // 220
    0x28, 0x44, 0x54, 0x54, 0x38, // 221
    0x7C, 0x10, 0x38, 0x44, 0x44, 0x44, 0x38, // 222
    0x48, 0x34, 0x14, 0x14, 0x7C, // 223
    0x70, 0x28, 0x28, 0x70, // 224  a
    0x38, 0x54, 0x54, 0x20, // 225
    0x7C, 0x54, 0x54, 0x28, // 226
    0x78, 0x08, 0x08, 0x08, // 227
    0x80, 0x70, 0x48, 0x48, 0x78, 0x80, // 228
    0x30, 0x48, 0x68, 0x58, // 229
    0x48, 0x30, 0x78, 0x30, 0x48, // 230
    0x28, 0x44, 0x54, 0x28, // 231
    0x78, 0x20, 0x10, 0x78, // 232
    0x79, 0x22, 0x12, 0x79, // 233
    0x78, 0x20, 0x10, 0x68, // 234
    0x40, 0x38, 0x08, 0x78, // 235
    0x78, 0x10, 0x20, 0x10, 0x78, // 236
    0x78, 0x10, 0x10, 0x78, // 237
    0x30, 0x48, 0x48, 0x30, // 238
    0x78, 0x08, 0x08, 0x78, // 239
    0xF8, 0x48, 0x48, 0x30, // 240
    0x30, 0x48, 0x48, 0x48, // 241
    0x08, 0x08, 0x78, 0x08, 0x08, // 242
    0x98, 0xA0, 0x60, 0x38, // 243
    0x10, 0x28, 0x7C, 0x28, 0x10, // 244
    0x48, 0x30, 0x30, 0x48, // 245
    0x78, 0x40, 0x40, 0x78, 0x80, // 246
    0x18, 0x20, 0x20, 0x78, // 247
    0x78, 0x40, 0x78, 0x40, 0x78, // 248
    0x78, 0x40, 0x78, 0x40, 0x78, 0x80, // 249
    0x08, 0x78, 0x50, 0x50, 0x20, // 250
    0x78, 0x50, 0x50, 0x20, 0x00, 0x78, // 251
    0x78, 0x50, 0x50, 0x20, // 252
    0x28, 0x44, 0x54, 0x38, // 253
    0x78, 0x30, 0x48, 0x48, 0x30, // 254
    0x50, 0x28, 0x28, 0x78 // 255
    
}; 
