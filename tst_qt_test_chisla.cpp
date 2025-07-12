#include "test_chisla.h"

void TestChisla::cleanupTestCase()
{
    //delete processor;
}

void TestChisla::init()
{
 processor = new NumberProcessor();
}

void TestChisla::cleanup()
{
  delete processor;
}


void TestChisla::testGcd()
{
    NumberProcessor B(0, 5);
    QCOMPARE(B.gcd(), 5);

    NumberProcessor C(48, 180);
    QCOMPARE(C.gcd(), 12);

    NumberProcessor A(1, 1);
    QVERIFY(A.gcd() == 1);

    NumberProcessor D(10, 2);
    QVERIFY(D.gcd() == 2);

    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, expected);

    processor->setNumbers(x, y);
    QCOMPARE(processor->gcd(), expected);


}


/*void TestChisla::testGcd1()
{
    processor->setNumbers(0, 5);
    QCOMPARE(processor->gcd(), 5);

    processor->setNumbers(48, 180);
    QCOMPARE(processor->gcd(), 12);

    processor->setNumbers(17, 23);
    QCOMPARE(processor->gcd(), 1);

    processor->setNumbers(10, 2);
    QVERIFY(processor->gcd() == 2);

    processor->setNumbers(0, 5);
    QCOMPARE(processor->gcd(), 5);
    processor->setNumbers(17, 23);
    QVERIFY(processor->gcd() == 1);
}
*/
void TestChisla::testGcd_data()
{
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("expected");

    QTest::newRow("GCD of 10 and 2") << 10 << 2 << 2;
    QTest::newRow("GCD of 17 and 23") << 17 << 23 << 1;
    QTest::newRow("GCD of 0 and 5") << 0 << 5 << 5;
    QTest::newRow("GCD of -12 and -18") << -12 << -18 << 6;
}

void TestChisla::testLcm()
{
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, expected);

    processor->setNumbers(x, y);
    QCOMPARE(processor->lcm(), expected);
}

void TestChisla::testLcm_data()
{
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("expected");

    QTest::newRow("lcm of 12 and 18") << 12 << 18 << 36;
    QTest::newRow("lcm of 5 and 7") << 5 << 7 << 35;
    QTest::newRow("lcm of 0 and 5") << 0 << 5 << 0;
}

void TestChisla::testArmstrong()
{
    QFETCH(int, number);
    QFETCH(bool, expected);

    processor->setNumbers(number, 0);
    QCOMPARE(processor->isXArmstrong(), expected);
}

void TestChisla::testArmstrong_data()
{
    QTest::addColumn<int>("number");
    QTest::addColumn<bool>("expected");

    QTest::newRow("153 is Armstrong") << 153 << true;
    QTest::newRow("370 is Armstrong") << 370 << true;
    QTest::newRow("123 is not Armstrong") << 123 << false;
    QTest::newRow("0 is not Armstrong") << 0 << false;
}

QTEST_APPLESS_MAIN(TestChisla)
