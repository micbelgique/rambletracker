namespace RambleTracker.DAL.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class TrackDate : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.Tracks", "Date", c => c.DateTime(nullable: false));
        }
        
        public override void Down()
        {
            DropColumn("dbo.Tracks", "Date");
        }
    }
}
