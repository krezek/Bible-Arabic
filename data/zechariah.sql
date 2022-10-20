DROP TABLE IF EXISTS zechariah;
CREATE VIRTUAL TABLE zechariah USING FTS5(chapter, verse, prefix, suffix, body);

.read zechariah/zechariah_1.sql
.read zechariah/zechariah_2.sql
.read zechariah/zechariah_3.sql
.read zechariah/zechariah_4.sql
.read zechariah/zechariah_5.sql
.read zechariah/zechariah_6.sql
.read zechariah/zechariah_7.sql
.read zechariah/zechariah_8.sql
.read zechariah/zechariah_9.sql
.read zechariah/zechariah_10.sql
.read zechariah/zechariah_11.sql
.read zechariah/zechariah_12.sql
.read zechariah/zechariah_13.sql
.read zechariah/zechariah_14.sql
