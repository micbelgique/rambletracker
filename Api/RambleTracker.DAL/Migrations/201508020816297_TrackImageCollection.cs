namespace RambleTracker.DAL.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class TrackImageCollection : DbMigration
    {
        public override void Up()
        {
            AddColumn("dbo.Images", "TrackId", c => c.Int(nullable: false));
            CreateIndex("dbo.Images", "TrackId");
            AddForeignKey("dbo.Images", "TrackId", "dbo.Tracks", "Id");
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.Images", "TrackId", "dbo.Tracks");
            DropIndex("dbo.Images", new[] { "TrackId" });
            DropColumn("dbo.Images", "TrackId");
        }
    }
}
