package main

import (
	_ "github.com/go-sql-driver/mysql"
	"github.com/tealeg/xlsx"
	"fmt"
	"database/sql"
)

const (
	DbUser = "root"
	DbPass = ""
	DbHost = "127.0.0.1"
	DbPort = "3306"
	DbName = "pm"
)

func main() {
	var url = DbUser + "@tcp(" + DbHost + ":" + DbPort + ")/" + DbName
	db, err := sql.Open("mysql", url)
	if err != nil {
		panic(err)
	}
	defer db.Close()
//	importSkills(db)
//	importLevel(db)
	importAbility(db)
}

func importAbility(db *sql.DB) {
	excelFileName := "ability.xlsx"
	xlFile, err := xlsx.OpenFile(excelFileName)
	if err != nil {
		panic(err)
	}
	for _, sheet := range xlFile.Sheets {
		for row_idx, row := range sheet.Rows {
			var items []string
			for _, cell := range row.Cells {
				if row_idx == 1 || row_idx == 0 {
					break;
				} else if cell.String() == "" {
					break;
				} else {
					items = append(items, cell.String())
				}
				//				fmt.Printf("row: %d, %s\n", row_idx, cell.String())
			}
			if(len(items) != 0) {
				for _, v := range items {

					fmt.Println(v)
				}

				sql := `insert into ability values (?, ?, ?)`

				stmt, err := db.Prepare(sql)
				if err != nil {
					panic(err)
				}
				stmt.Exec(items[0], items[1], items[2])

				fmt.Println("done")

			}
		}
	}
}

func importLevel(db *sql.DB) {
	excelFileName := "level.xlsx"
	xlFile, err := xlsx.OpenFile(excelFileName)
	if err != nil {
		panic(err)
	}
	for _, sheet := range xlFile.Sheets {
		for row_idx, row := range sheet.Rows {
			var items []string
			for _, cell := range row.Cells {
				if row_idx == 1 || row_idx == 0 {
					break;
				} else if cell.String() == "" {
					break;
				} else {
					items = append(items, cell.String())
				}
				//				fmt.Printf("row: %d, %s\n", row_idx, cell.String())
			}
			if(len(items) != 0) {
				for _, v := range items {

					fmt.Println(v)
				}

				sql := `insert into level values (?, ?, ?)`

				stmt, err := db.Prepare(sql)
				if err != nil {
					panic(err)
				}
				stmt.Exec(items[0], items[1], items[2])

				fmt.Println("done")

			}
		}
	}
}

func importSkills(db *sql.DB) {
	excelFileName := "skill.xlsx"
	xlFile, err := xlsx.OpenFile(excelFileName)
	if err != nil {

	}
	for _, sheet := range xlFile.Sheets {
		for row_idx, row := range sheet.Rows {
			var items []string
			for _, cell := range row.Cells {
				if row_idx == 1 || row_idx == 0 {
					break;
				} else if cell.String() == "" {
					break;
				} else {
					items = append(items, cell.String())
				}
//				fmt.Printf("row: %d, %s\n", row_idx, cell.String())
			}
			if(len(items) != 0) {
				for _, v := range items {

					fmt.Println(v)
				}

				sql := `insert into skill values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)`

				stmt, err := db.Prepare(sql)
				if err != nil {
					panic(err)
				}
				stmt.Exec(items[0], items[1], items[2],
						items[3], items[4], items[5],
						items[6], items[7], items[8],
						items[9], items[10], items[11],
						items[13], items[13], items[14],items[15])

				fmt.Println("done")

			}
		}
	}
}
