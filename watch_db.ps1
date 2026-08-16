$env:PGPASSWORD = 'postgres'

Write-Host "Starting Live Database Monitor..." -ForegroundColor Green
Start-Sleep -Seconds 1

while ($true) {
    Clear-Host
    Write-Host "=== LIVE DATABASE VIEW ===" -ForegroundColor Cyan
    Write-Host (Get-Date -Format "yyyy-MM-dd HH:mm:ss") -ForegroundColor DarkGray
    Write-Host ""
    
    Write-Host "--- USERS TABLE ---" -ForegroundColor Yellow
    & "C:\Program Files\PostgreSQL\18\bin\psql.exe" -U postgres -d banking_system -c "SELECT id, username, role FROM users;"
    
    Write-Host "--- ACCOUNTS TABLE ---" -ForegroundColor Yellow
    & "C:\Program Files\PostgreSQL\18\bin\psql.exe" -U postgres -d banking_system -c "SELECT account_id, user_id, balance, status FROM accounts;"
    
    Write-Host "--- RECENT TRANSACTIONS ---" -ForegroundColor Yellow
    & "C:\Program Files\PostgreSQL\18\bin\psql.exe" -U postgres -d banking_system -c "SELECT txn_id, account_id, type, amount, target_account_id, timestamp::timestamp(0) FROM transactions ORDER BY timestamp DESC LIMIT 10;"
    
    Write-Host "Press Ctrl+C to exit..." -ForegroundColor DarkGray
    Start-Sleep -Seconds 2
}
