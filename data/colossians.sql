DROP TABLE IF EXISTS colossians;
CREATE VIRTUAL TABLE colossians USING FTS5(chapter, verse, prefix, suffix, body);

.read colossians/colossians_1.sql
.read colossians/colossians_2.sql
.read colossians/colossians_3.sql
.read colossians/colossians_4.sql
