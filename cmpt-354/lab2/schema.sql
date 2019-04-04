-- df: null=0

CREATE TABLE Customers (  -- df: mult=1
    custid   INTEGER PRIMARY KEY,
    cname    VARCHAR(14), -- df: word=names.txt sub=power rate=0.016
    country  CHAR(3)      -- df: word=:GBR,USA,ITA,CHN,JPN
);

CREATE TABLE Products (   -- df: size=1000
    pcode    INTEGER PRIMARY KEY,
    pname    VARCHAR(10),
    pdesc    VARCHAR(20),
    ptype    VARCHAR(20),  -- df: word=:MUSIC,BOOK,MOVIE
    price    NUMERIC(6,2), -- df: float=gauss alpha=10 beta=3
    CHECK ( price > 0 )
);

CREATE TABLE Orders (     -- df: mult=20
    ordid    INTEGER PRIMARY KEY,
    odate    DATE,        -- df: start=2015-01-01 end=2016-09-30
    ocust    INTEGER NOT NULL REFERENCES Customers -- df: null=0
);

CREATE TABLE Details (    -- df: mult=40
    ordid    INTEGER REFERENCES Orders,   -- df: null=0
    pcode    INTEGER REFERENCES Products, -- df: null=0
    qty      SMALLINT,    -- df: int size=3 sub=power alpha=10
    PRIMARY KEY (ordid, pcode)
);

CREATE TABLE Invoices (    -- df: nogen
    invid    SERIAL PRIMARY KEY,
    ordid    INTEGER NOT NULL UNIQUE REFERENCES Orders,
    amount   NUMERIC(8,2) CHECK ( amount > 0 ),
    issued   DATE,
    due      DATE,
    CHECK ( due >= issued )
);

CREATE TABLE Payments (    -- df: nogen
    payid    INTEGER PRIMARY KEY,
    tstamp   TIMESTAMP,
    amount   NUMERIC(8,2) CHECK ( amount > 0 ),
    invid    INTEGER NOT NULL REFERENCES Invoices
);
