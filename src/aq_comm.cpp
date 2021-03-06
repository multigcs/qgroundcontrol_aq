#include "aq_comm.h"
#include <QMap>
#include <cmath>
#include <QDebug>
#include <QMap>
#include <QApplication>
#include "MG.h"

AQLogParser::AQLogParser()
{
    xValues.clear();
    yValues.clear();
    LoggerFrameSize = 0;
    if ( !xValues.contains("xvalue"))
        xValues.insert("xvalue", new QVector<double>());
}

AQLogParser::~AQLogParser()
{
}

void AQLogParser::ResetLog()
{
    xValues.clear();
    yValues.clear();
    LoggerFrameSize = 0;
}

int AQLogParser::ParseLogHeader(QString fileName)
{
    FILE *lf;
    fileName = QDir::toNativeSeparators(fileName);
    FileName = fileName;
    lf = fopen(fileName.toLocal8Bit().constData(),"rb");
    oldLog = false;
    xAxisCount = 0;
    if (lf) {
        LogChannelsStruct.clear();
        if (loggerReadHeader(lf) == 0 ) {
            fclose(lf);
            return 0;
        }
    }
    fclose(lf);
    return -1;
}

int AQLogParser::loggerReadHeader(FILE *fp)
{
    char ckA, ckB = 0;
    char ckA_Calculate, ckB_Calculate = 0;
    int i;
    int c = 0;
    uint8_t count_channels = 0;
    loggerFieldsAndActive_t fieldsInfo;
    LogChannelsStruct.clear();
    loggerTop:

    if (c != EOF) {
        if ((c = fgetc(fp)) != 'A')
            goto loggerTop;
        if ((c = fgetc(fp)) != 'q')
            goto loggerTop;
        if ((c = fgetc(fp)) != 'H') {
            if (c != 'L')
                goto loggerTop;
            else {
                oldLog = true;
                createHeaderL();
                return 0;
            }
        }

        count_channels = fgetc(fp);
        logHeader = (loggerFields_t*) calloc(count_channels , sizeof(loggerFields_t));
        fread(logHeader, sizeof(loggerFields_t), count_channels, fp);
        ckA_Calculate = 0;
        ckB_Calculate = 0;
        LoggerFrameSize = 0;
        ckA = fgetc(fp);
        ckB = fgetc(fp);
        ckA_Calculate += count_channels;
        ckB_Calculate += ckA_Calculate;
        for (i = 0; i<count_channels; i++) {
            ckA_Calculate += logHeader[i].fieldId;
            ckB_Calculate += ckA_Calculate;
            ckA_Calculate += logHeader[i].fieldType;
            ckB_Calculate += ckA_Calculate;
            fieldsInfo.fieldActive = false;
            fieldsInfo.fieldId = logHeader[i].fieldId;
            fieldsInfo.fieldType = logHeader[i].fieldType;
            fieldsInfo.fieldName = GetChannelsName(fieldsInfo.fieldId);
            LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));
//            qDebug() << "FieldID=" << logHeader[i].fieldId << " Name" << fieldsInfo.fieldName << " Type" << logHeader[i].fieldType << " list" << LogChannelsStruct.count();

            switch (fieldsInfo.fieldType) {
                case LOG_TYPE_DOUBLE:
                    LoggerFrameSize += 8;
                    break;
                case LOG_TYPE_FLOAT:
                case LOG_TYPE_U32:
                case LOG_TYPE_S32:
                    LoggerFrameSize += 4;
                    break;
                case LOG_TYPE_U16:
                case LOG_TYPE_S16:
                    LoggerFrameSize += 2;
                    break;
                case LOG_TYPE_U8:
                case LOG_TYPE_S8:
                    LoggerFrameSize += 1;
                    break;
            }
        }

        if (ckA_Calculate == ckA && ckB_Calculate == ckB) {
            free(logHeader);
            return 0;
        }
        else {
            LogChannelsStruct.clear();
            free(logHeader);
            qDebug() << "logger: checksum error\n";
            goto loggerTop;
        }
    }

    if (logHeader)
        free(logHeader);
    return -1;
}

QString AQLogParser::GetChannelsName(uint8_t fieldId)
{
    switch (fieldId) {
    case LOG_LASTUPDATE:
        return "LASTUPDATE";
        break;
    case LOG_VOLTAGE0:
        return "VOLTAGE0";
        break;
    case LOG_VOLTAGE1:
        return "VOLTAGE1";
        break;
    case LOG_VOLTAGE2:
        return "VOLTAGE2";
        break;
    case LOG_VOLTAGE3:
        return "VOLTAGE3";
        break;
    case LOG_VOLTAGE4:
        return "VOLTAGE4";
        break;
    case LOG_VOLTAGE5:
        return "VOLTAGE5";
        break;
    case LOG_VOLTAGE6:
        return "VOLTAGE6";
        break;
    case LOG_VOLTAGE7:
        return "VOLTAGE7";
        break;
    case LOG_VOLTAGE8:
        return "VOLTAGE8";
        break;
    case LOG_VOLTAGE9:
        return "VOLTAGE9";
        break;
    case LOG_VOLTAGE10:
        return "VOLTAGE10";
        break;
    case LOG_VOLTAGE11:
        return "VOLTAGE11";
        break;
    case LOG_VOLTAGE12:
        return "VOLTAGE12";
        break;
    case LOG_VOLTAGE13:
        return "VOLTAGE13";
        break;
    case LOG_VOLTAGE14:
        return "VOLTAGE14";
        break;
    case LOG_IMU_RATEX:
        return "IMU_RATEX";
        break;
    case LOG_IMU_RATEY:
        return "IMU_RATEY";
        break;
    case LOG_IMU_RATEZ:
        return "IMU_RATEZ";
        break;
    case LOG_IMU_ACCX:
        return "IMU_ACCX";
        break;
    case LOG_IMU_ACCY:
        return "IMU_ACCY";
        break;
    case LOG_IMU_ACCZ:
        return "IMU_ACCZ";
        break;
    case LOG_IMU_MAGX:
        return "IMU_MAGX";
        break;
    case LOG_IMU_MAGY:
        return "IMU_MAGY";
        break;
    case LOG_IMU_MAGZ:
        return "IMU_MAGZ";
        break;
    case LOG_GPS_PDOP:
        return "GPS_PDOP";
        break;
    case LOG_GPS_HDOP:
        return "GPS_HDOP";
        break;
    case LOG_GPS_VDOP:
        return "GPS_VDOP";
        break;
    case LOG_GPS_TDOP:
        return "GPS_TDOP";
        break;
    case LOG_GPS_NDOP:
        return "GPS_NDOP";
        break;
    case LOG_GPS_EDOP:
        return "GPS_EDOP";
        break;
    case LOG_GPS_ITOW:
        return "GPS_ITOW";
        break;
    case LOG_GPS_POS_UPDATE:
        return "GPS_POS_UPDATE";
        break;
    case LOG_GPS_LAT:
        return "GPS_LAT";
        break;
    case LOG_GPS_LON:
        return "GPS_LON";
        break;
    case LOG_GPS_HEIGHT:
        return "GPS_HEIGHT";
        break;
    case LOG_GPS_HACC:
        return "GPS_HACC";
        break;
    case LOG_GPS_VACC:
        return "GPS_VACC";
        break;
    case LOG_GPS_VEL_UPDATE:
        return "GPS_VEL_UPDATE";
        break;
    case LOG_GPS_VELN:
        return "GPS_VELN";
        break;
    case LOG_GPS_VELE:
        return "GPS_VELE";
        break;
    case LOG_GPS_VELD:
        return "GPS_VELD";
        break;
    case LOG_GPS_SACC:
        return "GPS_SACC";
        break;

    case LOG_ADC_PRESSURE1:
        return "ADC_PRESSURE1";
        break;
    case LOG_ADC_PRESSURE2:
        return "ADC_PRESSURE2";
        break;
    case LOG_ADC_TEMP0:
        return "ADC_TEMP0";
        break;

    case LOG_ADC_TEMP1:
        return "ADC_TEMP1";
        break;
    case LOG_ADC_TEMP2:
        return "ADC_TEMP2";
        break;

    case LOG_ADC_VIN:
        return "ADC_VIN";
        break;
    case LOG_ADC_MAG_SIGN:
        return "ADC_MAG_SIGN";
        break;
    case LOG_UKF_Q1:
        return "UKF_Q1";
        break;
    case LOG_UKF_Q2:
        return "UKF_Q2";
        break;
    case LOG_UKF_Q3:
        return "UKF_Q3";
        break;
    case LOG_UKF_Q4:
        return "UKF_Q4";
        break;
    case LOG_UKF_POSN:
        return "UKF_POSN";
        break;
    case LOG_UKF_POSE:
        return "UKF_POSE";
        break;
    case LOG_UKF_POSD:
        return "UKF_POSD";
        break;
    case LOG_UKF_PRES_ALT:
        return "UKF_PRES_ALT";
        break;
    case LOG_UKF_ALT:
        return "UKF_ALT";
        break;
    case LOG_UKF_VELN:
        return "UKF_VELN";
        break;
    case LOG_UKF_VELE:
        return "UKF_VELE";
        break;
    case LOG_UKF_VELD:
        return "UKF_VELD";
        break;
    case LOG_MOT_MOTOR0:
        return "MOT_MOTOR0";
        break;
    case LOG_MOT_MOTOR1:
        return "MOT_MOTOR1";
        break;
    case LOG_MOT_MOTOR2:
        return "MOT_MOTOR2";
        break;
    case LOG_MOT_MOTOR3:
        return "MOT_MOTOR3";
        break;
    case LOG_MOT_MOTOR4:
        return "MOT_MOTOR4";
        break;
    case LOG_MOT_MOTOR5:
        return "MOT_MOTOR5";
        break;
    case LOG_MOT_MOTOR6:
        return "MOT_MOTOR6";
        break;
    case LOG_MOT_MOTOR7:
        return "MOT_MOTOR7";
        break;
    case LOG_MOT_MOTOR8:
        return "MOT_MOTOR8";
        break;
    case LOG_MOT_MOTOR9:
        return "MOT_MOTOR9";
        break;
    case LOG_MOT_MOTOR10:
        return "MOT_MOTOR10";
        break;
    case LOG_MOT_MOTOR11:
        return "MOT_MOTOR11";
        break;
    case LOG_MOT_MOTOR12:
        return "MOT_MOTOR12";
        break;
    case LOG_MOT_MOTOR13:
        return "MOT_MOTOR13";
        break;

    case LOG_MOT_THROTTLE:
        return "MOT_THROTTLE";
        break;
    case LOG_MOT_PITCH:
        return "MOT_PITCH";
        break;
    case LOG_MOT_ROLL:
        return "MOT_ROLL";
        break;
    case LOG_MOT_YAW:
        return "MOT_YAW";
        break;
    case LOG_RADIO_QUALITY:
        return "RADIO_QUALITY";
        break;
    case LOG_RADIO_CHANNEL0:
        return "RADIO_CHANNEL0";
        break;
    case LOG_RADIO_CHANNEL1:
        return "RADIO_CHANNEL1";
        break;
    case LOG_RADIO_CHANNEL2:
        return "RADIO_CHANNEL2";
        break;
    case LOG_RADIO_CHANNEL3:
        return "RADIO_CHANNEL3";
        break;
    case LOG_RADIO_CHANNEL4:
        return "RADIO_CHANNEL4";
        break;
    case LOG_RADIO_CHANNEL5:
        return "RADIO_CHANNEL5";
        break;
    case LOG_RADIO_CHANNEL6:
        return "RADIO_CHANNEL6";
        break;
    case LOG_RADIO_CHANNEL7:
        return "RADIO_CHANNEL7";
        break;
    case LOG_RADIO_CHANNEL8:
        return "RADIO_CHANNEL8";
        break;
    case LOG_RADIO_CHANNEL9:
        return "RADIO_CHANNEL9";
        break;
    case LOG_RADIO_CHANNEL10:
        return "RADIO_CHANNEL10";
        break;
    case LOG_RADIO_CHANNEL11:
        return "RADIO_CHANNEL11";
        break;
    case LOG_RADIO_CHANNEL12:
        return "RADIO_CHANNEL12";
        break;
    case LOG_RADIO_CHANNEL13:
        return "RADIO_CHANNEL13";
        break;
    case LOG_RADIO_CHANNEL14:
        return "RADIO_CHANNEL14";
        break;
    case LOG_RADIO_CHANNEL15:
        return "RADIO_CHANNEL15";
        break;
    case LOG_RADIO_CHANNEL16:
        return "RADIO_CHANNEL16";
        break;
    case LOG_RADIO_CHANNEL17:
        return "RADIO_CHANNEL17";
        break;
    case LOG_RADIO_ERRORS:
        return "RADIO_ERRORS";
        break;
    case LOG_GMBL_TRIGGER:
        return "GMBL_TRIGGER";
        break;
    case LOG_ACC_BIAS_X:
        return "ACC_BIAS_X";
        break;
    case LOG_ACC_BIAS_Y:
        return "ACC_BIAS_Y";
        break;
    case LOG_ACC_BIAS_Z:
        return "ACC_BIAS_Z";
        break;
    case LOG_CURRENT_PDB:
        return "CURRENT_PDB";
        break;
    case LOG_CURRENT_EXT:
        return "CURRENT_EXT";
        break;
    case LOG_VIN_PDB:
        return "VIN_PDB";
        break;
    case LOG_UKF_ALT_VEL:
        return "UKF_ALT_VEL";
        break;
//    case LOG_NUM_IDS:
//        return "NUM_IDS";
//        break;
    default:
        return "Field_ID_" + QString::number(fieldId);
        break;

    }

}

void AQLogParser::GenerateChannelsCurve() {

    if ( !xValues.contains("XVALUES") )
        xValues.insert("XVALUES", new QVector<double>());

    for ( int i=0; i<LogChannelsStruct.count(); i++ ) {
        QPair<QString,loggerFieldsAndActive_t> val_pair = LogChannelsStruct.at(i);
        loggerFieldsAndActive_t val  = val_pair.second;
        if ( val.fieldActive == 1 )
            yValues.insert(val_pair.first, new QVector<double>());
    }

}

void AQLogParser::ShowCurves() {
    int n = 0;
    int count = 0;
    FILE *lf;
    QString fileName = QDir::toNativeSeparators(FileName);
    xValues.clear();
    yValues.clear();
    xAxisCount = 0;
    lf = fopen(fileName.toLocal8Bit().constData(),"rb");

    if (lf) {

        if (!oldLog) {
            GenerateChannelsCurve();
            CRCErrorCnt = 0;
            PosOfCrcError = 0;
            while (ParseLogM(lf) != EOF) {
                PosOfCrcError++;
                n++;
            }
        } else {
            count = 0;
            GenerateChannelsCurve();
            bool appendXvalues = true;
            for ( int i=0; i<LogChannelsStruct.count(); i++ ) {
                QPair<QString,loggerFieldsAndActive_t> val_pair = LogChannelsStruct.at(i);
                if ( val_pair.second.fieldActive == 1 ) {
                    rewind(lf);
                    while (loggerReadEntry(lf, &logEntry) != EOF) {
                        if ( appendXvalues) {
                            count++;
                            xValues.value("XVALUES")->append(count);
                        }
                        double va = logDumpGetValue(&logEntry, val_pair.second.fieldId);
                        yValues.value(val_pair.first)->append(va);
                    }
                    appendXvalues = false;
                }
            }
        }
    }
    fclose(lf);
}

int AQLogParser::ParseLogM(FILE *fp) {
    int c = 0;
    loggerTop:

    if (c != EOF) {
        if ((c = fgetc(fp)) != 'A')
            goto loggerTop;
        if ((c = fgetc(fp)) != 'q')
            goto loggerTop;

        c = fgetc(fp);
        if (c == 'M') {
            if (loggerReadEntryM(fp) == -1)
                goto loggerTop;
            else
                return 1;
        }
        else {
            goto loggerTop;
        }

    }

    return EOF;
}

int AQLogParser::loggerReadEntryM(FILE *fp) {
    char buffer[1024];
    char *buf = buffer;
    unsigned char ckA, ckB;
    int i;
    double tmp_double;
    float tmp_float;
    uint32_t tmp_uint32;
    int32_t tmp_int32;
    uint16_t tmp_uint16;
    int16_t tmp_int16;
    uint8_t tmp_uint8;
    int8_t tmp_int8;

    if (LoggerFrameSize > 0 && fread(buffer, LoggerFrameSize, 1, fp) == 1) {
        // calc checksum
        ckA = ckB = 0;
        for (i = 0; i < LoggerFrameSize; i++) {
            ckA += buf[i];
            ckB += ckA;
        }

        if (fgetc(fp) == ckA && fgetc(fp) == ckB) {
            xValues.value("XVALUES")->append(xAxisCount++);

            for ( int i=0; i<LogChannelsStruct.count(); i++ ) {
                QPair<QString,loggerFieldsAndActive_t> val_pair = LogChannelsStruct.at(i);
                loggerFieldsAndActive_t val  = val_pair.second;
                switch (val.fieldType) {
                case LOG_TYPE_DOUBLE:
                    if ( val.fieldActive == 1 )
                    {
                        tmp_double = *(double *)buf;
                        yValues.value(val.fieldName)->append(tmp_double);
                    }
                    buf += 8;
                    break;
                case LOG_TYPE_FLOAT:
                    if ( val.fieldActive == 1 )
                    {
                        tmp_float = *(float *)buf;
                        yValues.value(val.fieldName)->append(tmp_float);
                    }
                    buf += 4;
                    break;
                case LOG_TYPE_U32:
                    if ( val.fieldActive == 1 )
                    {
                        tmp_uint32 = *(uint32_t *)buf;
                        yValues.value(val.fieldName)->append(tmp_uint32);
                    }
                    buf += 4;
                    break;
                case LOG_TYPE_S32:
                    if ( val.fieldActive == 1 )
                    {
                        tmp_int32 = *(int32_t *)buf;
                        yValues.value(val.fieldName)->append(tmp_int32);
                    }
                    buf += 4;
                    break;
                case LOG_TYPE_U16:
                    if ( val.fieldActive == 1 )
                    {
                        tmp_uint16 = *(uint16_t *)buf;
                        yValues.value(val.fieldName)->append(tmp_uint16);
                    }
                    buf += 2;
                    break;
                case LOG_TYPE_S16:
                    if ( val.fieldActive == 1 )
                    {
                        tmp_int16 = *(int16_t *)buf;
                        yValues.value(val.fieldName)->append(tmp_int16);
                    }
                    buf += 2;
                    break;
                case LOG_TYPE_U8:
                    if ( val.fieldActive == 1 )
                    {
                        tmp_uint8 = *(uint8_t *)buf;
                        yValues.value(val.fieldName)->append(tmp_uint8);
                    }
                    buf += 1;
                    break;
                case LOG_TYPE_S8:
                    if ( val.fieldActive == 1 )
                    {
                        tmp_int8 = *(int8_t *)buf;
                        yValues.value(val.fieldName)->append(tmp_int8);
                    }
                    buf += 1;
                    break;
                }
            }
            return 1;
        }
        else {
            CRCErrorCnt++;
            qDebug() << "logger: checksum error " << CRCErrorCnt << " on frame " << PosOfCrcError;
        }

    }

    return -1;
}

void AQLogParser::createHeaderL() {
    LogChannelsStruct.clear();
    SetChannelsStruct();
}

void AQLogParser::SetChannelsStruct()
{
    loggerFieldsAndActive_t fieldsInfo;

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MICROS;
    fieldsInfo.fieldType = LOG_TYPE_U32;
    fieldsInfo.fieldName = "MICROS";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE1;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE1";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE2;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE2";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE3;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE3";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE4;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE4";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE5;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE5";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE6;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE6";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE7;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE7";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE8;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE8";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE9;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE9";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE10;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE10";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE11;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE11";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE12;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE12";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE13;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE13";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE14;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE14";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VOLTAGE15;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VOLTAGE15";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = RATEX;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "RATEX";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = RATEY;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "RATEY";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = RATEZ;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "RATEZ";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = ACCX;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "ACCX";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = ACCY;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "ACCY";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = ACCZ;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "ACCZ";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MAGX;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "MAGX";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MAGY;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "MAGY";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MAGZ;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "MAGZ";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = PRESSURE1;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "PRESSURE1";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = PRESSURE2;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "PRESSURE2";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = TEMP1;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "TEMP1";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = TEMP2;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "TEMP2";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = TEMP3;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "TEMP3";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = TEMP4;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "TEMP4";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = AUX_RATEX;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "AUX_RATEX";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = AUX_RATEY;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "AUX_RATEY";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = AUX_RATEZ;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "AUX_RATEZ";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = AUX_ACCX;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "AUX_ACCX";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = AUX_ACCY;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "AUX_ACCY";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = AUX_ACCZ;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "AUX_ACCZ";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));



    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = AUX_MAGX;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "AUX_MAGX";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = AUX_MAGY;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "AUX_MAGY";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = AUX_MAGZ;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "AUX_MAGZ";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = AUX_MAGZ;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "AUX_MAGZ";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VIN;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VIN";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = GPS_POS_UPDATE;
    fieldsInfo.fieldType = LOG_TYPE_U32;
    fieldsInfo.fieldName = "GPS_POS_UPDATE";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = LAT;
    fieldsInfo.fieldType = LOG_TYPE_DOUBLE;
    fieldsInfo.fieldName = "LAT";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = LON;
    fieldsInfo.fieldType = LOG_TYPE_DOUBLE;
    fieldsInfo.fieldName = "LON";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = GPS_ALT;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "GPS_ALT";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = GPS_POS_ACC;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "GPS_POS_ACC";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = GPS_VEL_UPDATE;
    fieldsInfo.fieldType = LOG_TYPE_U32;
    fieldsInfo.fieldName = "GPS_VEL_UPDATE";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));



    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = GPS_VELN;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "GPS_VELN";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = GPS_VELE;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "GPS_VELE";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = GPS_VELD;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "GPS_VELD";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = GPS_VEL_ACC;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "GPS_VEL_ACC";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));



    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = POSN;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "POSN";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = POSE;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "POSE";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = POSD;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "POSD";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VELN;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VELN";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VELE;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VELE";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = VELD;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "VELD";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = QUAT0;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "QUAT0";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = QUAT1;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "QUAT1";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = QUAT2;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "QUAT2";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = QUAT3;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "QUAT3";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));



    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR1;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR1";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR2;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR2";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR3;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR3";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR4;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR4";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR5;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR5";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR6;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR6";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR7;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR7";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR8;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR8";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR9;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR9";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR10;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR10";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR11;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR11";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR12;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR12";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR13;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR13";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = MOTOR14;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "MOTOR14";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = THROTTLE;
    fieldsInfo.fieldType = LOG_TYPE_U16;
    fieldsInfo.fieldName = "THROTTLE";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));


    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = EXTRA1;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "EXTRA1";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = EXTRA2;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "EXTRA2";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = EXTRA3;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "EXTRA3";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));

    fieldsInfo.fieldActive = false;
    fieldsInfo.fieldId = EXTRA4;
    fieldsInfo.fieldType = LOG_TYPE_FLOAT;
    fieldsInfo.fieldName = "EXTRA4";
    LogChannelsStruct.append(qMakePair(fieldsInfo.fieldName, fieldsInfo));
}

bool AQLogParser::getOldLog(){
    return oldLog;
}

#if defined(_MSC_VER) && _MSC_VER >= 1700
#pragma optimize("", off)
#endif
int AQLogParser::loggerReadEntry(FILE *fp, loggerRecord_t *r)
{
    char *buf = (char *)r;
    char ckA, ckB;
    int c = 0;

    while (c != EOF) {
        if ((c = fgetc(fp)) != 'A')
            continue;
        if ((c = fgetc(fp)) != 'q')
            continue;
        if ((c = fgetc(fp)) != 'L')
            continue;

        if (fread(buf, sizeof(loggerRecord_t), 1, fp) == 1) {
            // calc checksum
            ckA = ckB = 0;
            for (unsigned i = 0; i < sizeof(loggerRecord_t) - 2; i++) {
                ckA += buf[i];
                ckB += ckA;
            }

            if (r->ckA == ckA && r->ckB == ckB) {
                return 1;
            }
            else {
                qDebug() << "logger: checksum error\n";
                continue;
            }
        }
    }

    return -1;
}
#if defined(_MSC_VER) && _MSC_VER >= 1700
#pragma optimize("", on)
#endif

double AQLogParser::logDumpGetValue(loggerRecord_t *l, int field)
{
    double val;

    switch (field) {
    case MICROS:
        val =  l->lastUpdate;
        break;
    case VOLTAGE1:
        val = l->voltages[0];
        break;
    case VOLTAGE2:
        val = l->voltages[1];
        break;
    case VOLTAGE3:
        val = l->voltages[2];
        break;
    case VOLTAGE4:
        val = l->voltages[3];
        break;
    case VOLTAGE5:
        val = l->voltages[4];
        break;
    case VOLTAGE6:
        val = l->voltages[5];
        break;
    case VOLTAGE7:
        val = l->voltages[6];
        break;
    case VOLTAGE8:
        val = l->voltages[7];
        break;
    case VOLTAGE9:
        val = l->voltages[8];
        break;
    case VOLTAGE10:
        val = l->voltages[9];
        break;
    case VOLTAGE11:
        val = l->voltages[10];
        break;
    case VOLTAGE12:
        val = l->voltages[11];
        break;
    case VOLTAGE13:
        val = l->voltages[12];
        break;
    case VOLTAGE14:
        val = l->voltages[13];
        break;
    case VOLTAGE15:
        val = l->voltages[14];
        break;
    case RATEX:
        val = l->rate[0];
        break;
    case RATEY:
        val = l->rate[1];
        break;
    case RATEZ:
        val = l->rate[2];
        break;
    case ACCX:
        val = l->acc[0];
        break;
    case ACCY:
        val = l->acc[1];
        break;
    case ACCZ:
        val = l->acc[2];
        break;
    case MAGX:
        val = l->mag[0];
        break;
    case MAGY:
        val = l->mag[1];
        break;
    case MAGZ:
        val = l->mag[2];
        break;
    case PRESSURE1:
        val = l->pressure[0];
        break;
    case PRESSURE2:
        val = l->pressure[1];
        break;
    case TEMP1:
        val = l->temp[0];
        break;
    case TEMP2:
        val = l->temp[1];
        break;
    case TEMP3:
        val = l->temp[2];
        break;
    case TEMP4:
        val = l->temp[3];
        break;
    case AUX_RATEX:
        val = l->rateAux[0];
        break;
    case AUX_RATEY:
        val = l->rateAux[1];
        break;
    case AUX_RATEZ:
        val = l->rateAux[2];
        break;
    case AUX_ACCX:
        val = l->accAux[0];
        break;
    case AUX_ACCY:
        val = l->accAux[1];
        break;
    case AUX_ACCZ:
        val = l->accAux[2];
        break;
    case AUX_MAGX:
        val = l->magAux[0];
        break;
    case AUX_MAGY:
        val = l->magAux[1];
        break;
    case AUX_MAGZ:
        val = l->magAux[2];
        break;
    case VIN:
        val = l->vIn;
        break;
    case GPS_POS_UPDATE:
        val = l->gpsPosUpdate;
        break;
    case LAT:
        val = l->lat;
        break;
    case LON:
        val = l->lon;
        break;
    case GPS_ALT:
        val = l->gpsAlt;
        break;
    case GPS_POS_ACC:
        val = l->gpsPosAcc;
        break;
    case GPS_VEL_UPDATE:
        val = l->gpsVelUpdate;
        break;
    case GPS_VELN:
        val = l->gpsVel[0];
        break;
    case GPS_VELE:
        val = l->gpsVel[1];
        break;
    case GPS_VELD:
        val = l->gpsVel[2];
        break;
    case GPS_VEL_ACC:
        val = l->gpsVelAcc;
        break;
    case POSN:
        val = l->pos[0];
        break;
    case POSE:
        val = l->pos[1];
        break;
    case POSD:
        val = l->pos[2];
        break;
    case VELN:
        val = l->vel[0];
        break;
    case VELE:
        val = l->vel[1];
        break;
    case QUAT0:
        val = l->quat[0];
        break;
    case QUAT1:
        val = l->quat[1];
        break;
    case QUAT2:
        val = l->quat[2];
        break;
    case QUAT3:
        val = l->quat[3];
        break;
    case VELD:
        val = l->vel[2];
        break;
    case MOTOR1:
        val = l->motors[0];
        break;
    case MOTOR2:
        val = l->motors[1];
        break;
    case MOTOR3:
        val = l->motors[2];
        break;
    case MOTOR4:
        val = l->motors[3];
        break;
    case MOTOR5:
        val = l->motors[4];
        break;
    case MOTOR6:
        val = l->motors[5];
        break;
    case MOTOR7:
        val = l->motors[6];
        break;
    case MOTOR8:
        val = l->motors[7];
        break;
    case MOTOR9:
        val = l->motors[8];
        break;
    case MOTOR11:
        val = l->motors[9];
        break;
    case MOTOR12:
        val = l->motors[10];
        break;
    case MOTOR13:
        val = l->motors[11];
        break;
    case MOTOR14:
        val = l->motors[12];
        break;
    case THROTTLE:
        val = l->throttle;
        break;
    case EXTRA1:
        val = l->extra[0];
        break;
    case EXTRA2:
        val = l->extra[1];
        break;
    case EXTRA3:
        val = l->extra[2];
        break;
    case EXTRA4:
        val = l->extra[3];
        break;
    }

    return val;
}

int AQLogParser::GetFrameSize() {
    return LoggerFrameSize;
}

void AQLogParser::ReWriteFile(QString SourceFileName,QString DestinationFileName, int start1, int end1, int start2, int end2) {
    FILE *sf;
    QString fileNameSource;
    fileNameSource = QDir::toNativeSeparators(SourceFileName);
    sf = fopen(fileNameSource.toLocal8Bit().constData(),"rb");

    FILE *df;
    QString fileNameDestination;
    fileNameDestination = QDir::toNativeSeparators(DestinationFileName);
    df = fopen(fileNameDestination.toLocal8Bit().constData(),"wb");

    loggerWriteHeader(sf,df);

    if ( oldLog ) {
        loggerWriteDataL(sf,df, start1,end1,start2,end2);
    }
    else {
        loggerWriteDataM(sf,df, start1,end1,start2,end2);
    }


    fclose(sf);
    fclose(df);
}

int AQLogParser::loggerWriteHeader(FILE *fs, FILE *fd)
{
    char ckA, ckB = 0;
    char ckA_Calculate, ckB_Calculate = 0;
    int i;
    int c = 0;
    uint8_t count_channels = 0;
    loggerFieldsAndActive_t fieldsInfo;
    loggerTop:

    if (c != EOF) {
        if ((c = fgetc(fs)) != 'A')
            goto loggerTop;
        if ((c = fgetc(fs)) != 'q')
            goto loggerTop;
        if ((c = fgetc(fs)) != 'H') {
            if (c == 'L' ) {
                oldLog = true;
                return 0;
            }
            goto loggerTop;
        }
        oldLog = false;

        count_channels = fgetc(fs);
        logHeader = (loggerFields_t*) calloc(count_channels , sizeof(loggerFields_t));
        fread(logHeader, sizeof(loggerFields_t), count_channels, fs);
        ckA_Calculate = 0;
        ckB_Calculate = 0;
        LoggerFrameSize = 0;
        ckA = fgetc(fs);
        ckB = fgetc(fs);
        ckA_Calculate += count_channels;
        ckB_Calculate += ckA_Calculate;
        for (i = 0; i<count_channels; i++) {
            ckA_Calculate += logHeader[i].fieldId;
            ckB_Calculate += ckA_Calculate;
            ckA_Calculate += logHeader[i].fieldType;
            ckB_Calculate += ckA_Calculate;
            switch (logHeader[i].fieldType) {
                case LOG_TYPE_DOUBLE:
                    LoggerFrameSize += 8;
                    break;
                case LOG_TYPE_FLOAT:
                case LOG_TYPE_U32:
                case LOG_TYPE_S32:
                    LoggerFrameSize += 4;
                    break;
                case LOG_TYPE_U16:
                case LOG_TYPE_S16:
                    LoggerFrameSize += 2;
                    break;
                case LOG_TYPE_U8:
                case LOG_TYPE_S8:
                    LoggerFrameSize += 1;
                    break;
            }
        }

        if (ckA_Calculate == ckA && ckB_Calculate == ckB) {
            fputc('A',fd);
            fputc('q',fd);
            fputc('H',fd);
            fputc(count_channels,fd);
            fwrite(logHeader,sizeof(loggerFields_t),count_channels, fd);
            fputc(ckA,fd);
            fputc(ckB,fd);
            free(logHeader);
            return 0;
        }
        else {
            free(logHeader);
            qDebug() << "logger: checksum error\n";
            goto loggerTop;
        }
    }

    if (logHeader)
        free(logHeader);
    return -1;
}

void AQLogParser::loggerWriteDataM(FILE *fs, FILE *fd, int start1, int end1, int start2, int end2) {
    int c = 0;
    char buffer[1024];
    char *buf = buffer;
    unsigned char ckA, ckB;
    int i;
    int DataSetCount = 0;
    bool WriteToDestination = true;
    loggerTop:

    if (c != EOF) {
        if ((c = fgetc(fs)) != 'A')
            goto loggerTop;
        if ((c = fgetc(fs)) != 'q')
            goto loggerTop;

        c = fgetc(fs);
        if (c == 'M') {

            if (LoggerFrameSize > 0 && fread(buffer, LoggerFrameSize, 1, fs) == 1) {
                // calc checksum
                ckA = ckB = 0;
                for (i = 0; i < LoggerFrameSize; i++) {
                    ckA += buf[i];
                    ckB += ckA;
                }

                if (fgetc(fs) == ckA && fgetc(fs) == ckB) {
                    if ( DataSetCount == start1)
                        WriteToDestination = false;
                    if ( DataSetCount == end1)
                        WriteToDestination = true;

                    if ( DataSetCount == start2)
                        WriteToDestination = false;
                    if ( DataSetCount == end2)
                        WriteToDestination = true;

                    if ( WriteToDestination ) {
                        fputc('A',fd);
                        fputc('q',fd);
                        fputc('M',fd);
                        fwrite(buffer,LoggerFrameSize,1, fd);
                        fputc(ckA,fd);
                        fputc(ckB,fd);
                    }
                    DataSetCount++;
                }
                goto loggerTop;
            }
            else
                goto loggerTop;
        }
        else {
            goto loggerTop;
        }
    }
}

void AQLogParser::loggerWriteDataL(FILE *fs, FILE *fd, int start1, int end1, int start2, int end2) {
    int DataSetCount = 0;
    bool WriteToDestination = true;
    //read the full source file
    char buf[1024];
    //char *buf = buffer;

    char ckA_calc, ckB_calc;
    char ckA, ckB;
    uint i;
    int c = 0;

    loggerTop:

    if (c != EOF) {
        if ((c = fgetc(fs)) != 'A')
            goto loggerTop;
        if ((c = fgetc(fs)) != 'q')
            goto loggerTop;
        if ((c = fgetc(fs)) != 'L')
            goto loggerTop;

        if (fread(buf, sizeof(loggerRecord_t), 1, fs) == 1) {
            // calc checksum
            ckA_calc = 0;
            ckB_calc = 0;
            for (i = 0; i < sizeof(loggerRecord_t) - 2; i++) {
                ckA_calc += buf[i];
                ckB_calc += ckA_calc;
            }
            int ind = sizeof(loggerRecord_t);
            ckA = buf[ind-2];
            ckB = buf[ind-1];
            if (ckA_calc == ckA && ckB_calc == ckB) {
                if ( DataSetCount == start1)
                    WriteToDestination = false;
                if ( DataSetCount == end1)
                    WriteToDestination = true;

                if ( DataSetCount == start2)
                    WriteToDestination = false;
                if ( DataSetCount == end2)
                    WriteToDestination = true;

                if ( WriteToDestination ) {
                    fputc('A',fd);
                    fputc('q',fd);
                    fputc('L',fd);
                    fwrite(buf,sizeof(loggerRecord_t), 1, fd);
                    fputc(ckA,fd);
                    fputc(ckB,fd);
                }
                DataSetCount++;
                goto loggerTop;
            }
            else {
                fprintf(stderr, "logger: checksum error\n");
                goto loggerTop;
            }
        }
    }
}

//#######################################################################################################


AQEsc32::AQEsc32()
{
    fastSend = false;
    esc32BinaryMode = 0;
    esc32DoCommand = 0;
    StepMessageFromEsc32 = 1;
    TelemetryFrequenzy = 1000;
    esc32state = 0;
    esc32dataLogger = NULL;
    bootModeTimer = new QTimer(this);
}

AQEsc32::~AQEsc32()
{
}

void AQEsc32::Connect(QString port, QString baud)
{
    TimerState = 0;
    ExitCalibration = 0;
    fastSend = false;
    currentError = false;

    seriallinkEsc32 = new SerialLink(port, baud.toInt(), false, false, 8, 1);
    seriallinkEsc32->setEsc32Mode(false);
    connect(seriallinkEsc32, SIGNAL(connected()), this, SLOT(connectedEsc32()));
    connect(seriallinkEsc32, SIGNAL(communicationError(QString,QString)), this, SLOT(communicationErrorEsc32(QString,QString)));
    connect(seriallinkEsc32, SIGNAL(disconnected()), this, SLOT(disconnectedEsc32()));
    connect(seriallinkEsc32, SIGNAL(destroyed()), this, SLOT(destroyedEsc32()));
    connect(seriallinkEsc32, SIGNAL(bytesReceived(LinkInterface*, QByteArray)), this, SLOT(BytesRceivedEsc32(LinkInterface*, QByteArray)));
    seriallinkEsc32->connect();

    checkEsc32State = new QTimer(this);
    checkEsc32State->setInterval(10);
    checkEsc32State->stop();
    connect(checkEsc32State, SIGNAL(timeout()), this, SLOT(checkEsc32StateTimeOut()));

    if ( !esc32dataLogger )
        esc32dataLogger = new AQEsc32Logger();
}

void AQEsc32::Disconnect()
{
        seriallinkEsc32->setEsc32Mode(false);
        if (esc32BinaryMode) {
            SleepThread(500);
            SwitchFromBinaryToAscii();
            SleepThread(500);
        }
        checkEsc32State->stop();
        checkEsc32State = NULL;
        if ( esc32dataLogger )
            esc32dataLogger = NULL;

        seriallinkEsc32->disconnect();
}

void AQEsc32::SavePara(QString ParaName, QVariant ParaValue) {
    if ( !SwitchFromAsciiToBinary() )
        return;

    for ( int i = 0; i<5; i++) {
        StepMessageFromEsc32 = 4;
        ParaNameLastSend = ParaName;
        ParaLastSend = BINARY_COMMAND_SET;
        int paraToWrite =  getEnumByName(ParaName);
        float valueToWrite = ParaValue.toFloat();
        command_ACK_NACK = 0;
        esc32SendCommand(BINARY_COMMAND_SET,paraToWrite,valueToWrite,2);

        TimeOutWaiting = 0;
        while ( command_ACK_NACK != 250) {
            QCoreApplication::processEvents();
            SleepThread(5);
            TimeOutWaiting++;
            if (TimeOutWaiting > 100 ) {
                qDebug() << "Timeout " << i+1 << "of 5";
                break;
            }
        }
        if (command_ACK_NACK == 250 ){
            //qDebug() << "command ACK = 250";
            break;
        }

    }
}

void AQEsc32::sendCommand(int command, float Value1, float Value2, int num, bool withOutCheck ){
    if ( !SwitchFromAsciiToBinary() )
        return;

    command_ACK_NACK = 0;
    for ( int i = 0; i<5; i++) {
        StepMessageFromEsc32 = 4;
        ParaNameLastSend = "";
        ParaLastSend = command;
        LastParaValueSend1 = Value1;
        LastParaValueSend2 = Value2;
        esc32SendCommand(command,Value1,Value2,num);
        /*
        if ( i == 0)
            qDebug() << "Send command";
        else
            qDebug() << "Send command again";
        */
        if ( !withOutCheck ) {
            TimeOutWaiting = 0;
            while ( command_ACK_NACK != 250) {
                SleepThread(1);
                TimeOutWaiting++;
                if (TimeOutWaiting > 500 ) {
                    qDebug() << "Timeout " << i+1 << "of 5";
                    break;
                }
            }
        }
        else {
            command_ACK_NACK = 250;
            break;
        }

        if (command_ACK_NACK == 250 ){
            qDebug() << "command ACK = 250";
            break;
        }
    }
}

int AQEsc32::GetEsc32State() {
    return esc32state;
}

int AQEsc32::getEnumByName(QString Name)
{
    if ( Name == "CONFIG_VERSION")
        return CONFIG_VERSION;
    if ( Name == "STARTUP_MODE")
        return STARTUP_MODE;
    if ( Name == "BAUD_RATE")
        return BAUD_RATE;
    if ( Name == "PTERM")
        return PTERM;
    if ( Name == "ITERM")
        return ITERM;
    if ( Name == "FF1TERM")
        return FF1TERM;
    if ( Name == "FF2TERM")
        return FF2TERM;
    if ( Name == "CL1TERM")
        return CL1TERM;
    if ( Name == "CL2TERM")
        return CL2TERM;
    if ( Name == "CL3TERM")
        return CL3TERM;
    if ( Name == "CL4TERM")
        return CL4TERM;
    if ( Name == "CL5TERM")
        return CL5TERM;
    if ( Name == "SHUNT_RESISTANCE")
        return SHUNT_RESISTANCE;
    if ( Name == "MIN_PERIOD")
        return MIN_PERIOD;
    if ( Name == "MAX_PERIOD")
        return MAX_PERIOD;
    if ( Name == "BLANKING_MICROS")
        return BLANKING_MICROS;
    if ( Name == "ADVANCE")
        return ADVANCE;
    if ( Name == "START_VOLTAGE")
        return START_VOLTAGE;
    if ( Name == "GOOD_DETECTS_START")
        return GOOD_DETECTS_START;
    if ( Name == "BAD_DETECTS_DISARM")
        return BAD_DETECTS_DISARM;
    if ( Name == "MAX_CURRENT")
        return MAX_CURRENT;
    if ( Name == "SWITCH_FREQ")
        return SWITCH_FREQ;
    if ( Name == "MOTOR_POLES")
        return MOTOR_POLES;
    if ( Name == "PWM_MIN_PERIOD")
        return PWM_MIN_PERIOD;
    if ( Name == "PWM_MAX_PERIOD")
        return PWM_MAX_PERIOD;
    if ( Name == "PWM_MIN_VALUE")
        return PWM_MIN_VALUE;
    if ( Name == "PWM_LO_VALUE")
        return PWM_LO_VALUE;
    if ( Name == "PWM_HI_VALUE")
        return PWM_HI_VALUE;
    if ( Name == "PWM_MAX_VALUE")
        return PWM_MAX_VALUE;
    if ( Name == "PWM_MIN_START")
        return PWM_MIN_START;
    if ( Name == "PWM_RPM_SCALE")
        return PWM_RPM_SCALE;
    if ( Name == "FET_BRAKING")
        return FET_BRAKING;
    if ( Name == "PNFAC")
        return PNFAC;
    if ( Name == "INFAC")
        return INFAC;
    if ( Name == "THR1TERM")
        return THR1TERM;
    if ( Name == "THR2TERM")
        return THR2TERM;
    if ( Name == "START_ALIGN_TIME")
        return START_ALIGN_TIME;
    if ( Name == "START_ALIGN_VOLTAGE")
        return START_ALIGN_VOLTAGE;
    if ( Name == "START_STEPS_NUM")
        return START_STEPS_NUM;
    if ( Name == "START_STEPS_PERIOD")
        return START_STEPS_PERIOD;
    if ( Name == "START_STEPS_ACCEL")
        return START_STEPS_ACCEL;
    if ( Name == "PWM_LOWPASS")
        return PWM_LOWPASS;
    if ( Name == "RPM_MEAS_LP")
        return RPM_MEAS_LP;
    if ( Name == "SERVO_DUTY")
        return SERVO_DUTY;
    if ( Name == "SERVO_P")
        return SERVO_P;
    if ( Name == "SERVO_D")
        return SERVO_D;
    if ( Name == "SERVO_MAX_RATE")
        return SERVO_MAX_RATE;
    if ( Name == "SERVO_SCALE")
        return SERVO_SCALE;
    if ( Name == "ESC_ID")
        return ESC_ID;
    if ( Name == "DIRECTION")
        return DIRECTION;

    if ( Name == "CONFIG_NUM_PARAMS")
        return CONFIG_NUM_PARAMS;

    return 0;
}

void AQEsc32::connectedEsc32(){
    emit Esc32Connected();
}

void AQEsc32::disconnectedEsc32(){
    disconnect(seriallinkEsc32, 0, this, 0);
    seriallinkEsc32->deleteLater();
    seriallinkEsc32 = NULL;
    emit ESc32Disconnected();
}

void AQEsc32::destroyedEsc32(){
}

void AQEsc32::communicationErrorEsc32(QString err1, QString err2){
    Q_UNUSED(err1);
    Q_UNUSED(err2);
}

void AQEsc32::BytesRceivedEsc32(LinkInterface* link, QByteArray bytes){
    // Only add data from current link

    if ( link == seriallinkEsc32)
    {
        //unsigned char byte = bytes.at(j);
        switch (StepMessageFromEsc32)
        {
            case 0:
                // Parse all bytes
            break;

            //get ascii values for parameter
            case 1:
                LIST_MessageFromEsc32.append(QString(bytes));
                if ( LIST_MessageFromEsc32.contains("Command not found")) {
                    LIST_MessageFromEsc32 = "";
                    qDebug() << "Command not found";
                    return;
                }

                if ( LIST_MessageFromEsc32.contains("\r\n\r\n")) {
                    //decodeParameterFromEsc32(LIST_MessageFromEsc32);
                    emit ShowConfig(LIST_MessageFromEsc32);
                    //qDebug() << LIST_MessageFromEsc32;
                    LIST_MessageFromEsc32 = "";
                    SwitchFromAsciiToBinary();
                }
            break;

            // Waiting for a commit to ASCII mode
            case 2:
                ParaWriten_MessageFromEsc32.append(QString(bytes));
                ResponseFromEsc32.append(bytes);
                indexOfAqC = ParaWriten_MessageFromEsc32.indexOf("AqC");
                if (indexOfAqC > -1) {
                    checkInA = checkInB = 0;
                    int in = indexOfAqC+3;
                    commandLengthBack = ResponseFromEsc32[in];
                    esc32InChecksum(commandLengthBack);
                    in++;
                    command_ACK_NACK = ResponseFromEsc32[in];
                    esc32InChecksum(command_ACK_NACK);
                    in++;
                    commandSeqIdBack = ResponseFromEsc32[in];
                    esc32InChecksum(commandSeqIdBack);
                    in++;
                    commandBack = ResponseFromEsc32[in];
                    esc32InChecksum(commandBack);
                    in++;
                    unsigned char tmp_A = ResponseFromEsc32[in];
                    unsigned char tmp_B = ResponseFromEsc32[in+1];
                    if ((checkInA == tmp_A ) && (checkInB == tmp_B)) {
                        if ( command_ACK_NACK == 250) {
                            esc32BinaryMode = 0;
                            esc32state = 0;
                        }
                    }
                    ResponseFromEsc32.clear();
                    ParaWriten_MessageFromEsc32="";
                }

            break;

            // Waiting for a commit to binary mode
            case 3:
                ParaWriten_MessageFromEsc32.append(QString(bytes));
                if ( ParaWriten_MessageFromEsc32.contains("command mode...\r\n")) {
                    esc32BinaryMode = 1;
                    ParaWriten_MessageFromEsc32 = "";
                    esc32state = 1;
                }
            break;

            //Waiting for commit of send Parameter
            case 4:
                ParaWriten_MessageFromEsc32.append(QString(bytes));
                ResponseFromEsc32.append(bytes);
                indexOfAqC = ParaWriten_MessageFromEsc32.indexOf("AqC");
                reCheck:
                if (indexOfAqC > -1) {
                    checkInA = checkInB = 0;
                    int in = indexOfAqC+3;
                    commandLengthBack = ResponseFromEsc32[in];
                    esc32InChecksum(commandLengthBack);
                    in++;
                    command_ACK_NACK = ResponseFromEsc32[in];
                    esc32InChecksum(command_ACK_NACK);
                    in++;
                    commandSeqIdBack = ResponseFromEsc32[in];
                    //qDebug() << "commandSeqIdBack=" << commandSeqIdBack;
                    esc32InChecksum(commandSeqIdBack);
                    in++;
                    commandBack = ResponseFromEsc32[in];
                    //qDebug() << "commandBack=" << commandBack;
                    esc32InChecksum(commandBack);
                    in++;
                    unsigned char tmp_A = ResponseFromEsc32[in];
                    unsigned char tmp_B = ResponseFromEsc32[in+1];
                    if ((checkInA == tmp_A ) && (checkInB == tmp_B)) {
                        if ( ParaLastSend == BINARY_COMMAND_SET )
                            emit Esc32ParaWritten(ParaNameLastSend);
                        else
                            emit Esc32CommandWritten(ParaLastSend,LastParaValueSend1,LastParaValueSend2);

                        emit getCommandBack(commandBack);

                        if ( ParaLastSend == BINARY_COMMAND_START)
                            esc32state = 2;
                        if ( ParaLastSend == BINARY_COMMAND_STOP )
                            esc32state = 3;
                        if ( ParaLastSend == BINARY_COMMAND_ARM )
                            esc32state = 4;
                        if ( ParaLastSend == BINARY_COMMAND_DISARM )
                            esc32state = 5;
                    }
                    if ( ( in + 5) < ResponseFromEsc32.count()) {
                        indexOfAqC = ParaWriten_MessageFromEsc32.indexOf("AqC",in);
                        if ( indexOfAqC > -1 )
                            goto reCheck;
                    }
                    ResponseFromEsc32.clear();
                    ParaWriten_MessageFromEsc32="";
                }

            break;

            case 5:
                BootloaderMessage.append(QString(bytes));
                if ( BootloaderMessage.contains("Rebooting in boot loader mode...") ) {
                    bootModeTimer->stop();
                    emit EnteredBootMode();
                }
                else if ( BootloaderMessage.contains("ESC armed, disarm first") || BootloaderMessage.contains("Command not found") ) {
                    bootModeTimer->stop();
                    emit NoBootModeArmed(BootloaderMessage.remove(QRegExp("[^\\w\\s]")));
                }

                //qDebug() << BootloaderMessage;
            break;

            case 6:
                if (bytes.contains("ver")) {
                    firmwareVersion.append(bytes);
                    firmwareVersion.remove(QRegExp("(esc32|[^\\d\\.\\-])", Qt::CaseInsensitive));
                } else
                    firmwareVersion = "[unknown]";

                emit GotFirmwareVersion(firmwareVersion);
            break;

            default:
            break;
        }
    }
}

void AQEsc32::SetToBootMode() {
    QByteArray transmit;
    if (!SwitchFromBinaryToAscii())
        return;
    bootloaderInitReturned = false;
    BootloaderMessage = "";
    SleepThread(500);
    StepMessageFromEsc32 = 5;
    transmit.append("bootloader\n");
    if (!seriallinkEsc32 || !seriallinkEsc32->isConnected())
        return;
    seriallinkEsc32->writeBytes(transmit,transmit.size());

    bootModeTimer->setSingleShot(true);
    bootModeTimer->start(5000);
    connect(bootModeTimer, SIGNAL(timeout()), this, SLOT(emitBootModeTimeout()));
}

void AQEsc32::emitBootModeTimeout() {
    emit BootModeTimeout();
}

void AQEsc32::CheckVersion() {
    QByteArray transmit;
    if (!SwitchFromBinaryToAscii())
        return;
    SleepThread(500);
    StepMessageFromEsc32 = 6;
    transmit.append("version\n");
    if (!seriallinkEsc32 || !seriallinkEsc32->isConnected())
        return;
    seriallinkEsc32->writeBytes(transmit,transmit.size());
}

void AQEsc32::ReadConfigEsc32() {
    QByteArray transmit;
    if (!SwitchFromBinaryToAscii())
        return;
    SleepThread(500);
    StepMessageFromEsc32 = 1;
    transmit.append("set list\n");
    if (!seriallinkEsc32 || !seriallinkEsc32->isConnected())
        return;
    seriallinkEsc32->writeBytes(transmit,transmit.size());
}

int AQEsc32::SwitchFromAsciiToBinary()
{
    if (!seriallinkEsc32 || !seriallinkEsc32->isConnected())
        return 0;
    if (esc32BinaryMode)
        return 1;

    StepMessageFromEsc32 = 3;
    QByteArray transmit;
    transmit.append("binary\n");
    seriallinkEsc32->writeBytes(transmit,transmit.size());
    TimeOutWaiting = 0;
    while ( esc32BinaryMode == 0) {
        QCoreApplication::processEvents();
        TimeOutWaiting++;
        if (TimeOutWaiting > 100000 ) {
            qDebug() << "Error switch to binary mode!";
            return 0;
        }
    }
    return 1;
}

int AQEsc32::SwitchFromBinaryToAscii()
{
    if (!esc32BinaryMode)
        return 1;

    StepMessageFromEsc32 = 2;
    commandSeqIdBack = esc32SendCommand(BINARY_COMMAND_CLI, 0.0, 0.0, 0);
    TimeOutWaiting = 0;
    while ( esc32BinaryMode == 1) {
        QCoreApplication::processEvents();
        TimeOutWaiting++;
        if (TimeOutWaiting > 100000 ) {
            qDebug() << "Error switch to ascii mode!";
            return 0;
        }
    }
    return 1;
}

int AQEsc32::esc32SendCommand(unsigned char command, float param1, float param2, int n)
{
    if (!seriallinkEsc32 || !seriallinkEsc32->isConnected())
        return 0;
    QByteArray transmit;
    ResponseFromEsc32.clear();
    ParaWriten_MessageFromEsc32 = "";
    transmit.append("A");
    transmit.append("q");
    //################################
    seriallinkEsc32->writeBytes(transmit,transmit.size());
    checkOutA = 0;
    checkOutB = 0;
    command_ACK_NACK = 0;
    esc32SendChar(1 + 2 + n*sizeof(float));
    esc32SendChar(command);
    esc32SendShort(commandSeqId++);
    if (n > 0)
        esc32SendFloat(param1);
    if (n > 1)
        esc32SendFloat(param2);
    transmit.clear();
    transmit.append(checkOutA);
    transmit.append(checkOutB);
    seriallinkEsc32->writeBytes(transmit,transmit.size());

    return (commandSeqId - 1);
}

void AQEsc32::esc32SendChar(unsigned char c) {
    if (!seriallinkEsc32 || !seriallinkEsc32->isConnected())
        return;
    QByteArray transmit;
    transmit.append(c);
    seriallinkEsc32->writeBytes(transmit,transmit.size());
    esc32OutChecksum(c);
}

void AQEsc32::esc32SendShort(unsigned short i) {
    unsigned char j;
    unsigned char *c = (unsigned char *)&i;

    for (j = 0; j < sizeof(short); j++)
        esc32SendChar(*c++);
}

void AQEsc32::esc32SendFloat(float f) {
    unsigned char j;
    unsigned char *c = (unsigned char *)&f;

    for (j = 0; j < sizeof(float); j++)
        esc32SendChar(*c++);
}

void AQEsc32::esc32OutChecksum(unsigned char c) {
    checkOutA += c;
    checkOutB += checkOutA;
}

void AQEsc32::esc32InChecksum(unsigned char c) {
    checkInA += c;
    checkInB += checkInA;
}

SerialLink *AQEsc32::getSerialLink(){
    return seriallinkEsc32;
}

void AQEsc32::StartCalibration(float MaxCurrent, QString LogFile, QString ResFile) {
    Q_UNUSED(LogFile);
    LoggingFile = ""; //LogFile
    ResultFile = ResFile;
    maximum_Current = MaxCurrent;
    CommandBack = -1;
    TimerState = -2;
    ExitCalibration = 0;


    if ( ResultFile != "" )     {
        ResultFile = QDir::toNativeSeparators(ResultFile);
        #ifdef Q_OS_WIN
            calResultFile = fopen(ResultFile.toLocal8Bit().constData(),"w+");
        #else
            calResultFile = fopen(ResultFile.toLocal8Bit().constData(),"w+");
        #endif
    }

    //Timer starten
    checkEsc32State->start();
}

void AQEsc32::StopCalibration(bool withEmergencyExit) {
    if ( withEmergencyExit)
        ExitCalibration = 98;
    sendCommand(BINARY_COMMAND_STOP, 0.0, 0.0, 0, true);
    sendCommand(BINARY_COMMAND_TELEM_RATE, 0.0, 0.0, 1, true);
    sendCommand(BINARY_COMMAND_DISARM, 0.0, 0.0, 0, true);

}

void AQEsc32::StartLogging(){

	if (!seriallinkEsc32 || !seriallinkEsc32->isConnected())
		return;

    if (!seriallinkEsc32->getEsc32Mode()) {
        seriallinkEsc32->setEsc32Mode(false);
        sendCommand(BINARY_COMMAND_NOP, 0.0f, 0.0f, 0, false);

        sendCommand(BINARY_COMMAND_TELEM_RATE, 0.0, 0.0, 1, false);
        sendCommand(BINARY_COMMAND_TELEM_VALUE, 0.0f, BINARY_VALUE_VOLTS_BAT, 2, false);
        sendCommand(BINARY_COMMAND_TELEM_VALUE, 1.0f, BINARY_VALUE_VOLTS_BAT, 2, false);
        sendCommand(BINARY_COMMAND_TELEM_VALUE, 2.0f, BINARY_VALUE_VOLTS_BAT, 2, false);

        if ( esc32dataLogger ) {
            disconnect(seriallinkEsc32, SIGNAL(bytesReceived(LinkInterface*, QByteArray)), this, SLOT(BytesRceivedEsc32(LinkInterface*, QByteArray)));
            float freq = 1000;
            esc32dataLogger->startLoggingTelemetry(seriallinkEsc32,"");
            seriallinkEsc32->setEsc32Mode(true);
            sendCommand(BINARY_COMMAND_TELEM_RATE, freq, 0.0f, 1, true);
            esc32dataLogger->StartStopDecoding(true);
        }

    }
    else {
        sendCommand(BINARY_COMMAND_TELEM_RATE, 0.0, 0.0, 1, true);
        SleepThread(1000);
        esc32dataLogger->StartStopDecoding(false);
        seriallinkEsc32->setEsc32Mode(false);
        esc32dataLogger->stopLoggingTelemetry();
        SleepThread(1000);
        connect(this->seriallinkEsc32, SIGNAL(bytesReceived(LinkInterface*, QByteArray)), this, SLOT(BytesRceivedEsc32(LinkInterface*, QByteArray)));
    }

}

float AQEsc32::getFF1Term() {
    return FF1Term;
}

float AQEsc32::getFF2Term() {
    return FF2Term;
}

float AQEsc32::getCL1() {
    return CurrentLimiter1;
}

float AQEsc32::getCL2(){
    return CurrentLimiter2;
}

float AQEsc32::getCL3() {
    return CurrentLimiter3;
}

float AQEsc32::getCL4() {
    return CurrentLimiter4;
}

float AQEsc32::getCL5() {
    return CurrentLimiter5;
}

void AQEsc32::SetCalibrationMode(int mode) {
    calibrationMode = mode;
}

bool AQEsc32::RpmToVoltage(float maxAmps) {
    Eigen::MatrixXd A(2,2);
    Eigen::MatrixXd c(2,1);
    Eigen::MatrixXd ab(2,1);
    Eigen::MatrixXd data(100, 3);
    float f;
    int j;
    int i;
    FF1Term = 0;
    FF2Term = 0;
    f = 0;
    j = 0;
    i = 0;
    // reset max current
    SleepThread(100);
    if ( ExitCalibration != 0)
        return true;
    // reset Max Current
    esc32dataLogger->setTelemValueMaxs(0, 0.0f);
    esc32dataLogger->setTelemValueMaxs(1, 0.0f);
    esc32dataLogger->setTelemValueMaxs(2, 0.0f);
    currentError = false;

    printf("\n%5s %5s %5s\n", "RPM", "VOLTS", "AMPS");
    fprintf(calResultFile, "\n%5s %5s %5s\n", "RPM", "VOLTS", "AMPS");
    esc32dataLogger->StartStopDecoding(true);
    for (f = 4; f <= 100.0; f += 2.0) {
        sendCommand(BINARY_COMMAND_DUTY, f, 0.0f, 1, true);

        SleepThread(((100.0f - f) / 3.0f * 1e6 * 0.15)/1000);
        if ( ExitCalibration != 0)
            break;
        data(j,0) = esc32dataLogger->getTelemValueAvgs(0);
        data(j,1) = esc32dataLogger->getTelemValueAvgs(1);
        data(j,2) = esc32dataLogger->getTelemValueAvgs(2);
        printf("%5.0f %5.2f %5.2f\n", data(j,0), data(j,1), data(j,2));
        fprintf(calResultFile, "%5.0f %5.2f %5.2f\n", data(j,0), data(j,1), data(j,2));

        j++;

        if (esc32dataLogger->getTelemValueMaxs(2) > maxAmps){
            qDebug() << "max current = " << esc32dataLogger->getTelemValueMaxs(2);
            currentError = false;
            break;
        }
    }

    sendCommand(BINARY_COMMAND_TELEM_RATE, 0.0, 0.0, 1, true);
    SleepThread(1000);
    esc32dataLogger->StartStopDecoding(false);
    sendCommand(BINARY_COMMAND_STOP, 0.0, 0.0, 0, true);
    SleepThread(1000);
    sendCommand(BINARY_COMMAND_DISARM, 0.0, 0.0, 0, true);
    qDebug() << "Stopping";

    if ( esc32dataLogger->getTelemStorageNum() <= 0) {
        qDebug() << "No new Value in TelemStorage";
        return true;
    }

    A.setZero();
    c.setZero();
    for (i = 0; i < j; i++) {
        A(0, 0) += data(i,0)*data(i,0)*data(i,0)*data(i,0);
        A(0, 1) += data(i,0)*data(i,0)*data(i,0);
        A(1, 0) += data(i,0)*data(i,0)*data(i,0);
        A(1, 1) += data(i,0)*data(i,0);

        c(0) += data(i,0)*data(i,0)*data(i,1);
        c(1) += data(i,0)*data(i,1);
    }

    ab = A.inverse() * c;

    FF1Term = ab(0,0);
    FF2Term = ab(1,0);

    A.setZero();
    c.setZero();
    ab.setZero();
    data.setZero();
    qDebug() << "FF1Term =" << FF1Term;
    qDebug() << "FF2Term =" << FF2Term;

    fprintf(calResultFile, "FF1TERM\t%f\n", FF1Term);
    fprintf(calResultFile, "FF2TERM\t%f\n", FF2Term);
    fflush(calResultFile);
    fclose(calResultFile);
    calResultFile = NULL;
    return false;
}

bool AQEsc32::CurrentLimiter(float maxAmps) {
Eigen::MatrixXd A;
Eigen::MatrixXd c;
Eigen::MatrixXd ab;
Eigen::MatrixXd X;
int m,n;
int i, j, k, z;


    z = 0;
    qDebug() << "Starting...\n";
    sendCommand(BINARY_COMMAND_START, 0.0, 0.0, 0, true);
    SleepThread(1);
    currentError = false;
    if ( ExitCalibration != 0)
        return true;

    for (i = 10; i <= 90; i += 5) {
        qDebug() << "reset maxCurrent";
        esc32dataLogger->setTelemValueMaxs(2, 0.0f);
        for (j = i+5; j <= 100; j += 5) {
            esc32dataLogger->setTelemValueMaxs(2, 0.0f);
            stepUp((float)i, (float)j);
            printf("Duty %d to %d, MAX current = %f\n", i, j, esc32dataLogger->getTelemValueMaxs(2));
            fprintf(calResultFile, "Duty %d to %d, MAX current = %f\n", i, j, esc32dataLogger->getTelemValueMaxs(2));
            if ( ExitCalibration != 0)
                break;
            if (esc32dataLogger->getTelemValueMaxs(2) > maxAmps) {
                break;
            }
        }
        if ( ExitCalibration != 0)
            break;

        if (esc32dataLogger->getTelemValueMaxs(2) > maxAmps && j == i+5) {
            break;
        }
    }

    sendCommand(BINARY_COMMAND_TELEM_RATE, 0.0, 0.0, 1, true);
    SleepThread(1);
    sendCommand(BINARY_COMMAND_STOP, 0.0, 0.0, 0, true);
    SleepThread(1);
    sendCommand(BINARY_COMMAND_DISARM, 0.0, 0.0, 0, true);
    qDebug() << "Stopping";

    if ( esc32dataLogger->getTelemStorageNum() <= 0) {
        qDebug() << "Aborted esc32dataLogger->getTelemStorageNum()";
        return true;
    }

    n = esc32dataLogger->getTelemStorageNum();
    m = 5;
    X.setZero(n, m);
    A.setZero(m, m);
    c.setZero(m, 1);

    for (k = 0; k < n; k++) {
        X(k, 0) = 1.0;
        X(k, 1) = esc32dataLogger->getTelemStorage(MAX_TELEM_STORAGE*0 + k);
        X(k, 2) = esc32dataLogger->getTelemStorage(MAX_TELEM_STORAGE*2 + k);
        X(k, 3) = esc32dataLogger->getTelemStorage(MAX_TELEM_STORAGE*0 + k)*sqrt(fabs(esc32dataLogger->getTelemStorage(MAX_TELEM_STORAGE*2 + k)));
        X(k, 4) = sqrt(fabs(esc32dataLogger->getTelemStorage(MAX_TELEM_STORAGE*2 + k)));
    }

    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++)
            for (k = 0; k < n; k++)
                A(i, j) += X(k, i) * X(k, j);

        for (k = 0; k < n; k++)
            c(i, 0) += X(k, i) * esc32dataLogger->getTelemStorage(MAX_TELEM_STORAGE*1 + k);
    }

    ab = A.inverse() * c;

    CurrentLimiter1 = ab(0,0);
    CurrentLimiter2 = ab(1,0);
    CurrentLimiter3 = ab(2,0);
    CurrentLimiter4 = ab(3,0);
    CurrentLimiter5 = ab(4,0);

    fprintf(calResultFile, "CL1\t%f\n", CurrentLimiter1);
    fprintf(calResultFile, "CL2\t%f\n", CurrentLimiter2);
    fprintf(calResultFile, "CL3\t%f\n", CurrentLimiter3);
    fprintf(calResultFile, "CL4\t%f\n", CurrentLimiter4);
    fprintf(calResultFile, "CL5\t%f\n", CurrentLimiter5);
    fflush(calResultFile);
    fclose(calResultFile);
    calResultFile = NULL;
    A.setZero();
    c.setZero();
    ab.setZero();
    X.setZero();
    return false;
}

void AQEsc32::stepUp(float start, float end) {

    sendCommand(BINARY_COMMAND_DUTY, start, 0.0f, 1.0f, true);
    SleepThread(1500);
    if ( ExitCalibration != 0)
        return;
    sendCommand(BINARY_COMMAND_TELEM_RATE, TelemetryFrequenzy, 0.0f, 1, true);
    SleepThread(500);
    if ( ExitCalibration != 0)
        return;
    sendCommand(BINARY_COMMAND_DUTY, end, 0.0f, 1.0f, true);
    esc32dataLogger->StartStopDecoding(true);
    SleepThread(200);
    if ( ExitCalibration != 0)
        return;
    sendCommand(BINARY_COMMAND_TELEM_RATE, 0.0f, 0.0f, 1, true);
    SleepThread(500);
    esc32dataLogger->StartStopDecoding(false);
    if ( ExitCalibration != 0)
        return;
}

void AQEsc32::checkEsc32StateTimeOut() {
    if ( TimerState == -2) {
        qDebug() << "Send a Nop for testing com";
        sendCommand(BINARY_COMMAND_NOP, 0.0f, 0.0f, 0, false);
        TimerState = -1;
    }

    //Wait for binary nop
    if ( TimerState == -1 ) {
        if ((CommandBack == 0) || (command_ACK_NACK == 250)){
            CommandBack = -1;
            sendCommand(BINARY_COMMAND_ARM, 0.0f, 0.0f, 0, false);
            TimerState = 0;
            qDebug() << "send BINARY_COMMAND_ARM";
        }
    }

    //Wait for Arming
    if ( TimerState == 0 ) {
        if ((CommandBack == 0) || (command_ACK_NACK == 250)){
            CommandBack = -1;
            TimerState = 1;
            qDebug() << "get BINARY_COMMAND_ARM";
        }
    }
    // Send Stop to eSC32
    else if ( TimerState == 1 ) {
        CommandBack = -1;
        sendCommand(BINARY_COMMAND_STOP, 0.0f, 0.0f, 0, false);
        TimerState = 2;
        qDebug() << "send BINARY_COMMAND_STOP";
    }

    //Wait for Stop
    else if ( TimerState == 2 ) {
        if ((CommandBack == 0) || (command_ACK_NACK == 250)){
            CommandBack = -1;
            TimerState = 3;
            qDebug() << "get BINARY_COMMAND_STOP";
        }
    }
    // Send Tele rate to eSC32
    else if ( TimerState == 3 ) {
        CommandBack = -1;
        sendCommand(BINARY_COMMAND_TELEM_RATE, 0.0f, 0.0f, 1, false);
        qDebug() << "send BINARY_COMMAND_TELEM_RATE";
        TimerState = 4;
    }
    //Wait for Tele rate
    else if ( TimerState == 4 ) {
        if ((CommandBack == 0) || (command_ACK_NACK == 250)){
            CommandBack = -1;
            qDebug() << "get BINARY_COMMAND_TELEM_RATE";
            TimerState = 5;
        }
    }

    // Send Tele values to eSC32
    else if ( TimerState == 5 ) {
        CommandBack = -1;
        sendCommand(BINARY_COMMAND_TELEM_VALUE, 0.0f, BINARY_VALUE_RPM, 2, false);
        qDebug() << "send BINARY_COMMAND_TELEM_VALUE";
        TimerState = 6;
    }
    //Wait for Tele value
    else if ( TimerState == 6 ) {
        if ((CommandBack == 0) || (command_ACK_NACK == 250)){
            CommandBack = -1;
            qDebug() << "get BINARY_COMMAND_TELEM_VALUE";
            TimerState = 7;
        }
    }

    // Send Tele values to eSC32
    else if ( TimerState == 7 ) {
        CommandBack = -1;
        sendCommand(BINARY_COMMAND_TELEM_VALUE, 1.0f, BINARY_VALUE_VOLTS_MOTOR, 2, false);
        qDebug() << "send BINARY_COMMAND_TELEM_VALUE";
        TimerState = 8;
    }
    //Wait for Tele value
    else if ( TimerState == 8 ) {
        if ((CommandBack == 0) || (command_ACK_NACK == 250)){
            CommandBack = -1;
            qDebug() << "get BINARY_COMMAND_TELEM_VALUE";
            TimerState = 9;
        }
    }


    // Send Tele values to eSC32
    else if ( TimerState == 9 ) {
        CommandBack = -1;
        sendCommand(BINARY_COMMAND_TELEM_VALUE, 2.0f, BINARY_VALUE_AMPS, 2, false);
        qDebug() << "send BINARY_COMMAND_TELEM_VALUE";
        TimerState = 10;
    }
    //Wait for Tele value
    else if ( TimerState == 10 ) {
        if ((CommandBack == 0) || (command_ACK_NACK == 250)){
            CommandBack = -1;
            qDebug() << "get BINARY_COMMAND_TELEM_VALUE";
            TimerState = 11;
        }
    }


    // Send Tele values to eSC32
    else if ( TimerState == 11 ) {
        CommandBack = -1;
        sendCommand(BINARY_COMMAND_SET, MAX_CURRENT, 0.0f, 2, false);
        qDebug() << "send BINARY_COMMAND_SET";
        TimerState = 12;
    }
    //Wait for Max Currrent
    else if ( TimerState == 12 ) {
        if ((CommandBack == 0) || (command_ACK_NACK == 250)){
            CommandBack = -1;
            qDebug() << "get BINARY_COMMAND_SET";
            TimerState = 13;
        }
    }


    // Send Tele start to eSC32
    else if ( TimerState == 13 ) {
        CommandBack = -1;
        sendCommand(BINARY_COMMAND_START, 0.0f, 0.0f, 0, false);
        qDebug() << "send BINARY_COMMAND_START";
        TimerState = 14;
    }
    //Wait for start
    else if ( TimerState == 14 ) {
        if ((CommandBack == 0) || (command_ACK_NACK == 250)){
            CommandBack = -1;
            qDebug() << "get BINARY_COMMAND_START";
            TimerState = 15;
        }
    }

    // Send Tele duty to eSC32
    else if ( TimerState == 15 ) {
        CommandBack = -1;
        sendCommand(BINARY_COMMAND_DUTY, 4.0f, 0.0f, 1, false);
        qDebug() << "send BINARY_COMMAND_DUTY";
        TimerState = 16;
    }
    //Wait for start
    else if ( TimerState == 16 ) {
        if ((CommandBack == 0) || (command_ACK_NACK == 250)){
            CommandBack = -1;
            qDebug() << "get BINARY_COMMAND_DUTY";
            TimerState = 17;
        }
    }

    // Send Tele start to eSC32
    else if ( TimerState == 17 ) {
        CommandBack = -1;
        disconnect(this->seriallinkEsc32, SIGNAL(bytesReceived(LinkInterface*, QByteArray)), this, SLOT(BytesRceivedEsc32(LinkInterface*, QByteArray)));
        esc32dataLogger->startLoggingTelemetry(this->seriallinkEsc32, "");
        seriallinkEsc32->setEsc32Mode(true);
        if ( calibrationMode == 1) {
            sendCommand(BINARY_COMMAND_TELEM_RATE, TelemetryFrequenzy, 0.0, 1, true);
            TimerState = 18;
        }
        else if ( calibrationMode == 2) {
            TimerState = 19;
        }
        else {
            TimerState = 20;
        }
    }
    //Wait for start
    else if ( TimerState == 18 ) {
        qDebug() << "Start RPMToVoltag";
        RpmToVoltage(maximum_Current);
        TimerState = 20;
    }
    else if ( TimerState == 19 ) {
        qDebug() << "Start Current Limiter";
        CurrentLimiter(maximum_Current);
        TimerState = 20;
    }
    else if ( TimerState == 20 ) {
        CommandBack = -1;
        TimerState = -2;
        //Timer starten
        checkEsc32State->stop();
        seriallinkEsc32->setEsc32Mode(false);
        SleepThread(1000);
        esc32dataLogger->stopLoggingTelemetry();
        SleepThread(1000);
        connect(this->seriallinkEsc32, SIGNAL(bytesReceived(LinkInterface*, QByteArray)), this, SLOT(BytesRceivedEsc32(LinkInterface*, QByteArray)));
        if ( ExitCalibration != 0)
            emit finishedCalibration(ExitCalibration);
        else
            emit finishedCalibration(calibrationMode);
        ExitCalibration = 0;
    }
}

void AQEsc32::SetCommandBack(int Command) {
    CommandBack = Command;
}

void AQEsc32::SleepThread(int msec) {
    //MG::SLEEP::msleep(msec);

    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < dieTime){
        if ( ExitCalibration != 0)
            return;
        QCoreApplication::processEvents();
    }

}


//#######################################################################################################


AQEsc32Logger::AQEsc32Logger() {
}

AQEsc32Logger::~AQEsc32Logger() {
    free(TelemStorage);
}

void AQEsc32Logger::startLoggingTelemetry(SerialLink *link, QString FileName) {
    TelemStorage = (float *)calloc(MAX_TELEM_STORAGE, sizeof(float)*3);
    seriallinkEsc32 = link;
    TelemStorageNum = 0;
    bitsReceivedTotal = 0;
    StartStop = false;
    TelemOutFile = NULL;
    if ( FileName != "" )     {
        FileName = QDir::toNativeSeparators(FileName);
        #ifdef Q_OS_WIN
            TelemOutFile = fopen(FileName.toLocal8Bit().constData(),"w+");
        #else
            TelemOutFile = fopen(FileName.toLocal8Bit().constData(),"w+");
        #endif
    }
    connect(seriallinkEsc32, SIGNAL(teleReceived(QByteArray,int,int)), this, SLOT(teleDataReceived(QByteArray,int,int)));
}

void AQEsc32Logger::StartStopDecoding(bool Start) {
    dataMutex.lock();
    this->StartStop = Start;
    dataMutex.unlock();
}

void AQEsc32Logger::teleDataReceived(QByteArray data, int rows, int cols){
    checkInA =  0;
    checkInB = 0;
    int i,j;
    esc32InChecksum(rows);
    esc32InChecksum(cols);
    int count_For_measuring = 0;
    for (i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            TelemData[i][j] = esc32GetFloat(data,count_For_measuring);
            count_For_measuring += sizeof(float);
        }
    }
    unsigned char tmp_A  = data[count_For_measuring+0];
    unsigned char tmp_B  = data[count_For_measuring+1];

    if ((checkInA == tmp_A ) && (checkInB == tmp_B)) {
        bitsReceivedTotal++;
        if (( MG::TIME::getGroundTimeNow() - connectionStartTime) > 1000) {
            //qDebug() << "get " << bitsReceivedTotal << "Messages " << rows << " " << cols;
            bitsReceivedTotal = 0;
            connectionStartTime = MG::TIME::getGroundTimeNow();
        }
        if (!StartStop)
            return;

        // update averages
        for (i = 0; i < rows; i++){
            for (j = 0; j < cols; j++){
                //Average
                TelemValueAvgs[j] -= (TelemValueAvgs[j] - TelemData[i][j]) * 0.01;
            }
        }
        // update Max
        for (i = 0; i < rows; i++){
            for (j = 0; j < cols; j++){
                //Max
                if (TelemValueMaxs[j] < TelemData[i][j]){
                    TelemValueMaxs[j] = TelemData[i][j];
                }
            }
        }
        // save to memory
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                TelemStorage[MAX_TELEM_STORAGE*j + TelemStorageNum] = TelemData[i][j];
            }
            if ( TelemStorageNum < MAX_TELEM_STORAGE)
                TelemStorageNum++;
            else
                TelemStorageNum = MAX_TELEM_STORAGE;
        }

    }
}

void AQEsc32Logger::stopLoggingTelemetry() {
    disconnect(seriallinkEsc32, SIGNAL(teleReceived(QByteArray,int,int)), this, SLOT(teleDataReceived(QByteArray,int,int)));
    if (TelemOutFile) {
        fclose(TelemOutFile);
    }
}

void AQEsc32Logger::run() {
}

unsigned short AQEsc32Logger::esc32GetShort(QByteArray data, int startIndex) {
    unsigned short s;
    for ( unsigned i =0; i< sizeof(unsigned short); i++) {
        esc32InChecksum(data[startIndex+i]);
    }
    QByteArray b = data.mid(startIndex,sizeof(unsigned short));
    unsigned short * buf = (unsigned short *) b.data();
    s = *buf;
    return s;
}

float AQEsc32Logger::esc32GetFloat(QByteArray data, int startIndex) {

    float f;
    unsigned char *c = (unsigned char *)&f;
    unsigned int i;

    for (i = 0; i < sizeof(float); i++) {
        esc32InChecksum(data[startIndex+i]);
        *c++ = data[startIndex+i];
    }
    return f;
}

void AQEsc32Logger::esc32InChecksum(unsigned char c) {
    checkInA += c;
    checkInB += checkInA;
}

float AQEsc32Logger::getTelemValueAvgs(int index){
    dataMutex.lock();
    float ret;
    if ( TelemValueAvgs)
        ret = TelemValueAvgs[index];
    else
        ret = 0.0;
    dataMutex.unlock();
    return ret;
}

void AQEsc32Logger::setTelemValueMaxs(int index ,float value) {
    dataMutex.lock();
    TelemValueMaxs[index] = value;
    dataMutex.unlock();
}

float AQEsc32Logger::getTelemValueMaxs(int index){
    dataMutex.lock();
    float ret = TelemValueMaxs[index];
    dataMutex.unlock();
    return ret;
}

float AQEsc32Logger::getTelemStorage(int index) {
    dataMutex.lock();
    float ret = TelemStorage[index];
    dataMutex.unlock();
    return ret;
}

int AQEsc32Logger::getTelemStorageNum() {
    return TelemStorageNum;
}
