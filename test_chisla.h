#ifndef TST_CHISLA_H
#define TST_CHISLA_H
#include "chisla.h"
#include <QtTest>

class TestChisla : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void cleanupTestCase();

    void testGcd();
    void testLcm();
    void testArmstrong();
    void testLcm_data();
    void testArmstrong_data();
    void testGcd_data();


private:
    NumberProcessor* processor;
};

#endif // TST_CHISLA_H
