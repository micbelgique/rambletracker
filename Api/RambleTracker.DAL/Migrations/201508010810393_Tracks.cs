using System.Data.Entity.Migrations;

namespace RambleTracker.DAL.Migrations
{
    public partial class Tracks : DbMigration
    {
        public override void Up()
        {
            Sql("TRUNCATE TABLE [PositionDatas]");
            CreateTable(
                "dbo.Tracks",
                c => new
                    {
                        Id = c.Int(nullable: false, identity: true),
                    })
                .PrimaryKey(t => t.Id);
            
            AddColumn("dbo.PositionDatas", "TrackId", c => c.Int(nullable: false));
            CreateIndex("dbo.PositionDatas", "TrackId");
            AddForeignKey("dbo.PositionDatas", "TrackId", "dbo.Tracks", "Id");
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.PositionDatas", "TrackId", "dbo.Tracks");
            DropIndex("dbo.PositionDatas", new[] { "TrackId" });
            DropColumn("dbo.PositionDatas", "TrackId");
            DropTable("dbo.Tracks");
        }
    }
}
