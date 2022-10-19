DROP TABLE IF EXISTS song_of_solomon;
CREATE VIRTUAL TABLE song_of_solomon USING FTS5(chapter, verse, prefix, suffix, body);

.read song_of_solomon/song_of_solomon_1.sql
.read song_of_solomon/song_of_solomon_2.sql
.read song_of_solomon/song_of_solomon_3.sql
.read song_of_solomon/song_of_solomon_4.sql
.read song_of_solomon/song_of_solomon_5.sql
.read song_of_solomon/song_of_solomon_6.sql
.read song_of_solomon/song_of_solomon_7.sql
.read song_of_solomon/song_of_solomon_8.sql
