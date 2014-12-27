CREATE TABLE history (
    whenquery timestamp without time zone NOT NULL,
    udc smallint NOT NULL,
    idc smallint NOT NULL,
    ul1 smallint NOT NULL,
    il1 smallint NOT NULL,
    pac smallint NOT NULL,
    prl smallint NOT NULL,
    tkk smallint NOT NULL,
    tnf smallint NOT NULL,
    kdy smallint NOT NULL
);

COMMENT ON COLUMN history.whenquery IS 'Timestamp';
COMMENT ON COLUMN history.udc IS 'DC Voltage';
COMMENT ON COLUMN history.idc IS 'DC Current';
COMMENT ON COLUMN history.ul1 IS 'AC Voltage';
COMMENT ON COLUMN history.il1 IS 'AC Current';
COMMENT ON COLUMN history.pac IS 'Output power';
COMMENT ON COLUMN history.tkk IS 'Inverter temperature';
COMMENT ON COLUMN history.tnf IS 'AC Output frequency';
COMMENT ON COLUMN history.kdy IS 'Today production';

ALTER TABLE ONLY history
    ADD CONSTRAINT history_pkey PRIMARY KEY (whenquery);
