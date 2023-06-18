//
// Created by cychen on 2023/3/10.
//

#ifndef LIST_ERRORCODE_H
#define LIST_ERRORCODE_H

// 文件错误
#define NOT_EXIST_FILE (-1) //done
#define ILLEGAL_FILE (-2) //done
#define LACK_OF_FILE (-98) //done
#define MORE_THAN_ONE_FILE (-97) //done
// 参数使用错误
#define NOT_EXIST_PARAMETER (-3) //done
#define DUPLICATE_PARAMETER (-4) //done
#define MORE_THAN_ONE_CHAR (-5) //done
#define LACK_OF_CHAR (-6) //done
#define MORE_THAN_ONE_STATE (-7) //done
#define LACK_OF_STATE (-8) //done
#define NOT_EXIST_RING_PARA (-9)
#define ILLEGAL_PARAMETER_VALUE (-10) //done
#define UNEXPECTED_PARAMETER (-96) //done
// 参数不兼容
#define NOT_COMPATIBLE_PARAMETER (-11) //not to implement
#define HEAD_TAIL_LIMIT_SAME (-12) //done
#define HEAD_LIMIT_CONTRADICTION (-13) //done
// 内部异常
#define TYPE_MISMATCH (-14)
// ...
// 其他错误
#define UNDEFINED_EXCEPTION (-99)

#define NO_INFO ("NO INFO")
#endif //LIST_ERRORCODE_H
