DROP TABLE IF EXISTS matthew_pho;
CREATE TABLE matthew_pho (chapter INTEGER, verse INTEGER, pho BLOB);

INSERT INTO matthew_pho (chapter, verse, pho) VALUES (1, 1, readfile("../pho/matthew/matthew_1/matthew_1_1.pho"));