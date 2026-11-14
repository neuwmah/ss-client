void CheckHeroLogin() {
    if (connection == 1) return;
    if (!*heroConnected) return;
    connection = 1;
    ReadItemsTable();
}