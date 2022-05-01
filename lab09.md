1.
UNF:
Order [CK OrderNo, Orderdate, CustNo, CustLname, (PartNo, PartDesc, QtyOrd, Price)]
1NF:
Order [CK OrderNo, OrderDate, CustNo, CustLname]
OrderPart [CK PartNo, FK OrderNo, PartDesc, QtyOrd, Price]
2NF:
Order [CK OrderNo, CK OrderDate]
CustOrder [CK CustNo, FK OrderNo]
Customer [CK CustNo, CustLname]
Part [CK PartNo, PartDesc, Price]
OrderPart [FK OrderNo, FK PartNo, QtdOrd]
3NF:
Order [CK OrderNo, CK OrderDate]
CustOrder [CK CustNo, FK OrderNo]
Customer [CK CustNo, CustLname]
Part [CK PartNo, FK PartDesc]
OrderPart [FK OrderNo, FK PartNo, QtdOrd]
PricePart [CK PartDesc, Price]

2.
UNF:
REPORT [CK Serial, (Model, Price, Color, Name, Year)]

1NF:
REPORT [CK Serial, FK Model]
MODELDETAIL [CK Model, CK Name, Price, Color, Year]
2NF:
REPORT [CK Serial, FK Model]
MODELPRICE [CK Model, Price]
MODELDETAIL [CK Name, Color, Year]
3NF
REPORT [CK Serial, FK Model]
MODELPRICE [CK Model, Price, FK Serial]
MODELDETAIL [CK Name, Color, Year, FK Model]

3.
UNF: Rental [CK FullName, Address, (Movies), Salutation]

1NF:
User [CK FullName, Address, Salutation]
Rental [CK Movies, FK FullName]
2NF:
User [CK FullName, Address, Salutation]
Rental [CK RentID, Movies, FK FullName]
3NF:
User [CK FullName, Address, Salutation]
Rental [CK RentID, Movies]
RentalByName [FK RentID, FK FullName]
